#include <QMessageBox>

#include "Background.qoh"
#include "BackgroundCtrl.qoh"

#include "BackgroundCtrlPanel.qoh"


BackgroundCtrlPanel::BackgroundCtrlPanel(QWidget* parent)
:   QLabel(parent),
    m_bgCtrl(NULL)
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

void BackgroundCtrlPanel::Associate(BackgroundCtrl* ctrl)
{
    if (ctrl == m_bgCtrl)
        return;

    m_selectionGrp->setEnabled(false);

    if (m_bgCtrl)
    {
        m_backgroundGlobMute->disconnect(m_bgCtrl);
        m_globalVolSld->disconnect(m_bgCtrl);
        m_selectionMuteChk->disconnect(m_bgCtrl);
        m_selectionVolSld->disconnect(m_bgCtrl);
        m_bgCtrl->disconnect(SIGNAL(destroyed(QObject*)), this);
        m_bgCtrl->SelectionModel()->disconnect(this);
    }

    m_bgCtrl = ctrl;
    if (!ctrl)
    {
        setEnabled(false);
        m_globalVolSld->setValue(0);
        m_backgroundGlobMute->setChecked(false);
        m_selectionVolSld->setValue(0);
        m_selectionMuteChk->setChecked(false);
        return;
    }

    setEnabled(true);
    m_effectList->setModel(ctrl->Model());
    m_effectList->setSelectionModel(ctrl->SelectionModel());
    m_globalVolSld->setValue(ctrl->GetMasterVolume());
    m_backgroundGlobMute->setChecked(ctrl->IsMasterMuted());
    m_selectionVolSld->setValue(0);
    m_selectionMuteChk->setChecked(false);

    connect( m_globalVolSld,        SIGNAL( valueChanged(int)       ),
             ctrl,                  SLOT  ( SetMasterVolume(int)    ) );
    connect( m_backgroundGlobMute,  SIGNAL( toggled(bool)           ),
             ctrl,                  SLOT  ( SetMasterMuted(bool)    ) );
    connect( ctrl->SelectionModel(),
             SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
             this,
             SLOT( UpdateSelectionControls() ) );
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
        emit DeleteSelected( (*it).data().toString() );
    }
}

void BackgroundCtrlPanel::RemoveCtrl()
{
    setEnabled(false);
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
            Background* bgSel = m_bgCtrl->GetInstance(selection[0].data().toString());

            m_selectionVolSld->setValue(bgSel->GetInstanceVolume());
            m_selectionMuteChk->setChecked(bgSel->IsInstancePaused());
        }

        for ( QModelIndexList::iterator it = selection.begin();
              it != selection.end();
              it++ )
        {
            Background* bgSel = m_bgCtrl->GetInstance((*it).data().toString());

            connect(m_selectionMuteChk, SIGNAL( toggled(bool)           ),
                    bgSel,              SLOT  ( SetInstancePaused(bool) ) );
            connect(m_selectionVolSld,  SIGNAL( valueChanged(int)       ),
                    bgSel,              SLOT  ( SetInstanceVolume(int)  ) );
        }
    }
}
