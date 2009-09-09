#include <QMessageBox>

#include "Background.h"
#include "I_ImportTarget.h"
#include "MasterCtrl.qoh"
#include "State.qoh"
#include "TitleCarrierListModel.hpp"

#include "BackgroundCtrlPanel.qoh"


BackgroundCtrlPanel::BackgroundCtrlPanel(QWidget* parent)
:   QLabel(parent),
    m_bgCtrl(NULL),
    m_bgListModel(NULL)
{
    setupUi(this);
    setBackgroundRole(QPalette::Window);
    setFrameStyle(QFrame::WinPanel);
    setAutoFillBackground(true);
    setEnabled(false);

    m_bgListModel = new TitleCarrierListModel;
    m_effectList->setModel(m_bgListModel);

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

BackgroundCtrlPanel::~BackgroundCtrlPanel()
{
    delete m_bgListModel;
}

void BackgroundCtrlPanel::Associate(State* state)
{
    MasterCtrl* ctrl = NULL;
    if (state)
        ctrl = state->GetBackgroundController();

    if (ctrl == m_bgCtrl)
        return;

    m_selectionGrp->setEnabled(false);

    if (m_bgCtrl)
    {
        m_backgroundGlobMute->disconnect(m_bgCtrl);
        m_globalVolSld->disconnect(m_bgCtrl);
        m_selectionMuteChk->disconnect();
        m_selectionVolSld->disconnect();
        m_bgCtrl->disconnect(SIGNAL(destroyed()), this);
    }

    m_bgCtrl = ctrl;
    if (!ctrl)
    {
        setEnabled(false);
        m_globalVolSld->setValue(0);
        m_backgroundGlobMute->setChecked(false);
        m_selectionVolSld->setValue(0);
        m_selectionMuteChk->setChecked(false);
        m_bgListModel->setList( QList<I_TitleCarrier*>() );
        return;
    }

    setEnabled(true);
    m_bgListModel->setList(ctrl->Children());
    m_globalVolSld->setValue(ctrl->Volume());
    m_backgroundGlobMute->setChecked(ctrl->IsPaused());
    m_selectionVolSld->setValue(0);
    m_selectionMuteChk->setChecked(false);

    connect( m_globalVolSld,        SIGNAL( valueChanged(int)   ),
             ctrl,                  SLOT  ( SetVolume(int)      ) );
    connect( m_backgroundGlobMute,  SIGNAL( toggled(bool)       ),
             ctrl,                  SLOT  ( SetPaused(bool)     ) );
    connect( ctrl,                  SIGNAL( ChildListChanged()  ),
             this,                  SLOT  ( UpdateList()        ) );
    connect( ctrl,                  SIGNAL( destroyed()         ),
             this,                  SLOT  ( RemoveCtrl()        ) );
}

void BackgroundCtrlPanel::OnAddSelected()
{
    class ImportTarget : public I_ImportTarget
    {
        MasterCtrl* m_ctrl;
    public:
        ImportTarget(MasterCtrl* ctrl) : m_ctrl(ctrl) { }
        virtual void AddImport(A_SoundImport* import)
        {
            Background* instance = new Background(import);
            m_ctrl->AddInstance(instance);
        }
    } *importTarget = new ImportTarget(m_bgCtrl);

    emit AddSelected(importTarget);
    delete importTarget;
}

void BackgroundCtrlPanel::OnDeleteSelected()
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
    for ( QModelIndexList::iterator it = selected.begin();
          it != selected.end();
          it++ )
    {
        delete (*it).data(Qt::UserRole).value<I_TitleCarrier*>();
    }
}

void BackgroundCtrlPanel::RemoveCtrl()
{
    setEnabled(false);

    m_backgroundGlobMute->disconnect(m_bgCtrl);
    m_globalVolSld->disconnect(m_bgCtrl);
    m_selectionMuteChk->disconnect();
    m_selectionVolSld->disconnect();

    m_globalVolSld->setValue(0);
    m_backgroundGlobMute->setChecked(false);
    m_selectionVolSld->setValue(0);
    m_selectionMuteChk->setChecked(false);
    m_bgCtrl = NULL;
}

void BackgroundCtrlPanel::UpdateSelectionControls()
{
    m_selectionMuteChk->disconnect();
    m_selectionVolSld->disconnect();

    if (!m_effectList->selectionModel())
    {
        m_selectionGrp->setEnabled(false);
        m_selectionMuteChk->setChecked(false);
        m_selectionVolSld->setValue(0);
        return;
    }

    QModelIndexList selection = m_effectList->selectionModel()->selectedIndexes();

    if (selection.size() == 0)
    {
        m_selectionGrp->setEnabled(false);
        m_selectionMuteChk->setChecked(false);
        m_selectionVolSld->setValue(0);
    }
    else
    {
        m_selectionGrp->setEnabled(true);

        if (selection.size() == 1)
        {
            Background* bgSel = dynamic_cast<Background*>(
                selection[0].data(Qt::UserRole).value<I_TitleCarrier*>()
                );

            m_selectionVolSld->setValue(bgSel->InstanceVolume());
            m_selectionMuteChk->setChecked(bgSel->IsInstancePaused());
        }

        for ( QModelIndexList::iterator it = selection.begin();
              it != selection.end();
              it++ )
        {
            Background* bgSel = dynamic_cast<Background*>(
                (*it).data(Qt::UserRole).value<I_TitleCarrier*>()
                );

            connect(m_selectionMuteChk, SIGNAL( toggled(bool)           ),
                    bgSel,              SLOT  ( SetInstancePaused(bool) ) );
            connect(m_selectionVolSld,  SIGNAL( valueChanged(int)       ),
                    bgSel,              SLOT  ( SetInstanceVolume(int)  ) );
        }
    }
}

void BackgroundCtrlPanel::UpdateList()
{
    m_bgListModel->setList(m_bgCtrl->Children());
}
