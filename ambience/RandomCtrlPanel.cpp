#include <QMessageBox>

#include "I_ImportTarget.h"
#include "MasterCtrl.qoh"
#include "RandomSound.qoh"
#include "State.qoh"
#include "TitleCarrierListModel.hpp"

#include "RandomCtrlPanel.qoh"


RandomCtrlPanel::RandomCtrlPanel(QWidget* parent)
:   QLabel(parent),
    m_randCtrl(NULL),
    m_randListModel(NULL)
{
    setupUi(this);
    setBackgroundRole(QPalette::Window);
    setFrameStyle(QFrame::WinPanel);
    setAutoFillBackground(true);
    setEnabled(false);

    m_randListModel = new TitleCarrierListModel;
    m_effectList->setModel(m_randListModel);

    connect( m_addBtn,          SIGNAL( clicked()           ),
             this,              SLOT  ( OnAddSelected()     ) );
    connect( m_deleteBtn,       SIGNAL( clicked()           ),
             this,              SLOT  ( OnDeleteSelected()  ) );
    connect( m_selectAllBtn,    SIGNAL( clicked()           ),
             m_effectList,      SLOT  ( selectAll()         ) );
    connect( m_deselectAllBtn,  SIGNAL( clicked()           ),
             m_effectList,      SLOT  ( clearSelection()    ) );
    connect( m_effectList->selectionModel(),
             SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
             this,
             SLOT( UpdateSelectionControls() ) );
}

void RandomCtrlPanel::Associate(State* state)
{
    MasterCtrl* ctrl = NULL;
    if (state)
        ctrl = state->GetRandomController();

    if (m_randCtrl == ctrl)
        return;

    m_selectionGrp->setEnabled(false);

    if (m_randCtrl)
    {
        m_globalMuteChk->disconnect(m_randCtrl);
        m_globalVolSld->disconnect(m_randCtrl);
        m_selectionMuteChk->disconnect();
        m_selectionVolSld->disconnect();
        m_selectionVarSld->disconnect();
        m_selectionPerValSpn->disconnect();
        m_selectionPerTypeCbo->disconnect();
        m_randCtrl->disconnect(SIGNAL(destroyed()), this);
    }

    m_randCtrl = ctrl;
    if (!ctrl)
    {
        setEnabled(false);
        m_globalVolSld->setValue(0);
        m_globalMuteChk->setChecked(false);
        m_selectionVolSld->setValue(0);
        m_selectionVarSld->setValue(0);
        m_selectionPerValSpn->setValue(0.0);
        m_selectionPerTypeCbo->setEditText("");
        m_selectionMuteChk->setChecked(false);
        m_randListModel->setList( QList<I_TitleCarrier*>() );
        return;
    }

    setEnabled(true);
    m_randListModel->setList(ctrl->Children());
    m_globalVolSld->setValue(ctrl->Volume());
    m_globalMuteChk->setChecked(ctrl->IsPaused());
    m_selectionVolSld->setValue(0);
    m_selectionVarSld->setValue(0);
    m_selectionPerValSpn->setValue(0.0);
    m_selectionPerTypeCbo->setEditText("");
    m_selectionMuteChk->setChecked(false);

    connect( m_globalVolSld,    SIGNAL( valueChanged(int)   ),
             ctrl,              SLOT  ( SetVolume(int)      ) );
    connect( m_globalMuteChk,   SIGNAL( toggled(bool)       ),
             ctrl,              SLOT  ( SetPaused(bool)     ) );
    connect( ctrl,              SIGNAL( ChildListChanged()  ),
             this,              SLOT  ( UpdateList()        ) );
    connect( ctrl,              SIGNAL( destroyed()         ),
             this,              SLOT  ( RemoveCtrl()        ) );
}

void RandomCtrlPanel::OnAddSelected()
{
    class ImportTarget : public I_ImportTarget
    {
        MasterCtrl* m_ctrl;
    public:
        ImportTarget(MasterCtrl* ctrl) : m_ctrl(ctrl) { }
        virtual void AddImport(A_SoundImport* import)
        {
            RandomSound* instance = new RandomSound(import);
            m_ctrl->AddInstance(instance);
        }
    } *importTarget = new ImportTarget(m_randCtrl);

    emit AddSelected(importTarget);
    delete importTarget;
}

void RandomCtrlPanel::OnDeleteSelected()
{
    QMessageBox::StandardButtons result =
        QMessageBox::warning(
            this,
            "Remove sound",
            "Are you sure you want to remove the selected sounds from the playlist?",
            QMessageBox::Yes | QMessageBox::No );
    if (result != QMessageBox::Yes)
        return;

    QModelIndexList selected = m_effectList->selectionModel()->selectedIndexes();
    QStringList selectedTitles;
    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        delete (*it).data(Qt::UserRole).value<I_TitleCarrier*>();
    }
}

void RandomCtrlPanel::RemoveCtrl()
{
    setEnabled(false);

    m_globalMuteChk->disconnect(m_randCtrl);
    m_globalVolSld->disconnect(m_randCtrl);
    m_selectionMuteChk->disconnect();
    m_selectionVolSld->disconnect();
    m_selectionVarSld->disconnect();
    m_selectionPerValSpn->disconnect();
    m_selectionPerTypeCbo->disconnect();

    m_globalVolSld->setValue(0);
    m_globalMuteChk->setChecked(false);
    m_selectionVolSld->setValue(0);
    m_selectionVarSld->setValue(0);
    m_selectionPerValSpn->setValue(0.0);
    m_selectionPerTypeCbo->setEditText("");
    m_selectionMuteChk->setChecked(false);
    m_randCtrl = NULL;
}

void RandomCtrlPanel::UpdateSelectionControls()
{
    m_selectionMuteChk->disconnect();
    m_selectionVolSld->disconnect();
    m_selectionVarSld->disconnect();
    m_selectionPerValSpn->disconnect();
    m_selectionPerTypeCbo->disconnect();

    if (!m_effectList->selectionModel())
    {
        m_selectionGrp->setEnabled(false);
        m_selectionMuteChk->setChecked(false);
        m_selectionVolSld->setValue(0);
        m_selectionVarSld->setValue(0);
        m_selectionPerValSpn->setValue(0.0);
        m_selectionPerTypeCbo->setEditText("");
        return;
    }

    QModelIndexList selection = m_effectList->selectionModel()->selectedIndexes();

    if (selection.size() == 0)
    {
        m_selectionGrp->setEnabled(false);
        m_selectionMuteChk->setChecked(false);
        m_selectionVolSld->setValue(0);
        m_selectionVarSld->setValue(0);
        m_selectionPerValSpn->setValue(0.0);
        m_selectionPerTypeCbo->setEditText("");
    }
    else
    {
        m_selectionGrp->setEnabled(true);

        if (selection.size() == 1)
        {
            RandomSound* randSel = dynamic_cast<RandomSound*>(
                selection[0].data(Qt::UserRole).value<I_TitleCarrier*>()
                );

            m_selectionVolSld->setValue(randSel->InstanceVolume());
            m_selectionMuteChk->setChecked(randSel->IsInstancePaused());
            m_selectionVarSld->setValue(randSel->Variance());
            m_selectionPerValSpn->setValue(randSel->Period());
            m_selectionPerTypeCbo->setCurrentIndex((int)randSel->GetPeriodType());
        }

        for ( QModelIndexList::iterator it = selection.begin();
              it != selection.end();
              it++ )
        {
            RandomSound* randSel = dynamic_cast<RandomSound*>(
                (*it).data(Qt::UserRole).value<I_TitleCarrier*>()
                );

            connect(m_selectionMuteChk,     SIGNAL( toggled(bool)               ),
                    randSel,                SLOT  ( SetInstancePaused(bool)     ) );
            connect(m_selectionVolSld,      SIGNAL( valueChanged(int)           ),
                    randSel,                SLOT  ( SetInstanceVolume(int)      ) );
            connect(m_selectionVarSld,      SIGNAL( valueChanged(int)           ),
                    randSel,                SLOT  ( SetVariance(int)            ) );
            connect(m_selectionPerValSpn,   SIGNAL( valueChanged(double)        ),
                    randSel,                SLOT  ( SetPeriod(double)           ) );
            connect(m_selectionPerTypeCbo,  SIGNAL( currentIndexChanged(int)    ),
                    randSel,                SLOT  ( SetPeriodType(int)          ) );
        }
    }
}

void RandomCtrlPanel::UpdateList()
{
    m_randListModel->setList(m_randCtrl->Children());
}
