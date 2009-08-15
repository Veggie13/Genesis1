#include <QMessageBox>

#include "RandomCtrl.qoh"
#include "RandomSound.qoh"

#include "RandomCtrlPanel.qoh"


RandomCtrlPanel::RandomCtrlPanel(QWidget* parent)
:   QLabel(parent),
    m_randCtrl(NULL)
{
    setupUi(this);
    setBackgroundRole(QPalette::Window);
    setFrameStyle(QFrame::WinPanel);
    setAutoFillBackground(true);
    setEnabled(false);

    connect( m_addBtn,          SIGNAL( clicked()           ),
             this,              SIGNAL( AddSelected()       ) );
    connect( m_deleteBtn,       SIGNAL( clicked()           ),
             this,              SLOT  ( OnDeleteSelected()  ) );
    connect( m_selectAllBtn,    SIGNAL( clicked()           ),
             m_effectList,      SLOT  ( selectAll()         ) );
    connect( m_deselectAllBtn,  SIGNAL( clicked()           ),
             m_effectList,      SLOT  ( clearSelection()    ) );
}

void RandomCtrlPanel::Associate(RandomCtrl* ctrl)
{
    if (m_randCtrl == ctrl)
        return;

    m_selectionGrp->setEnabled(false);

    if (m_randCtrl)
    {
        m_globalMuteChk->disconnect(m_randCtrl);
        m_globalVolSld->disconnect(m_randCtrl);
        m_selectionMuteChk->disconnect(m_randCtrl);
        m_selectionVolSld->disconnect(m_randCtrl);
        m_selectionVarSld->disconnect(m_randCtrl);
        m_selectionPerValSpn->disconnect(m_randCtrl);
        m_selectionPerTypeCbo->disconnect(m_randCtrl);
        m_randCtrl->disconnect(SIGNAL(destroyed(QObject*)), this);
        m_randCtrl->SelectionModel()->disconnect(this);
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
        return;
    }

    setEnabled(true);
    m_effectList->setModel(ctrl->Model());
    m_effectList->setSelectionModel(ctrl->SelectionModel());
    m_globalVolSld->setValue(ctrl->GetMasterVolume());
    m_globalMuteChk->setChecked(ctrl->IsMasterMuted());
    m_selectionVolSld->setValue(0);
    m_selectionVarSld->setValue(0);
    m_selectionPerValSpn->setValue(0.0);
    m_selectionPerTypeCbo->setEditText("");
    m_selectionMuteChk->setChecked(false);

    connect( m_globalVolSld,    SIGNAL( valueChanged(int)       ),
             ctrl,              SLOT  ( SetMasterVolume(int)    ) );
    connect( m_globalMuteChk,   SIGNAL( toggled(bool)           ),
             ctrl,              SLOT  ( SetMasterMuted(bool)    ) );
    connect( ctrl->SelectionModel(),
             SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
             this,
             SLOT( UpdateSelectionControls() ) );
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
        emit DeleteSelected( (*it).data().toString() );
    }
}

void RandomCtrlPanel::RemoveCtrl()
{
    setEnabled(false);
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
            RandomSound* randSel =
                m_randCtrl->GetInstance(selection[0].data().toString());

            m_selectionVolSld->setValue(randSel->GetInstanceVolume());
            m_selectionMuteChk->setChecked(!randSel->IsInstanceActive());
            m_selectionVarSld->setValue(randSel->GetVariance());
            m_selectionPerValSpn->setValue(randSel->GetPeriod());
            m_selectionPerTypeCbo->setCurrentIndex(randSel->GetPeriodType());
        }

        for ( QModelIndexList::iterator it = selection.begin();
              it != selection.end();
              it++ )
        {
            RandomSound* randSel =
                m_randCtrl->GetInstance((*it).data().toString());

            connect(m_selectionMuteChk,     SIGNAL( toggled(bool)               ),
                    randSel,                SLOT  ( SetInstanceInactive(bool)   ) );
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
