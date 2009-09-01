#include <QMessageBox>

#include "MusicCtrl.qoh"
#include "QException.h"
#include "StartableSound.qoh"
#include "TitleCarrierListModel.hpp"

#include "MusicCtrlPanel.qoh"


MusicCtrlPanel::MusicCtrlPanel(QWidget* parent)
:   QLabel(parent),
    m_musicCtrl(NULL),
    m_musicListModel(NULL)
{
    setupUi(this);
    setBackgroundRole(QPalette::Window);
    setFrameStyle(QFrame::WinPanel);
    setAutoFillBackground(true);
    setEnabled(false);

    m_musicListModel = new TitleCarrierListModel;
    m_playlistCbo->setModel(m_musicListModel);

    connect( m_addBtn,      SIGNAL( clicked()           ),
             this,          SIGNAL( AddSelected()       ) );
    connect( m_deleteBtn,   SIGNAL( clicked()           ),
             this,          SLOT  ( OnDeleteSelected()  ) );
    connect( m_playlistCbo, SIGNAL( currentIndexChanged(int) ),
             this,          SLOT  ( ChangeSong(int)          ) );
}

void MusicCtrlPanel::Associate(MusicCtrl* ctrl)
{
    if (ctrl == m_musicCtrl)
        return;

    if (m_musicCtrl)
    {
        disconnect(m_musicCtrl);
        m_musicVolumeSld->disconnect(m_musicCtrl);
        m_musicMuteChk->disconnect(m_musicCtrl);
        m_musicCtrl->disconnect(this);
    }

    m_musicCtrl = ctrl;
    if (!ctrl)
    {
        setEnabled(false);
        return;
    }

    setEnabled(true);
    m_musicListModel->setList(ctrl->Children());

    m_musicVolumeSld->setValue(ctrl->Volume());
    m_musicMuteChk->setChecked(ctrl->IsPaused());

    connect( m_musicVolumeSld,  SIGNAL( valueChanged(int) ),
             ctrl,              SLOT  ( SetVolume(int)    ) );
    connect( m_musicMuteChk,    SIGNAL( toggled(bool)     ),
             ctrl,              SLOT  ( SetPaused(bool)   ) );

    connect( this,              SIGNAL( SongSelected(StartableSound*)   ),
             ctrl,              SLOT  ( SetCurrentSong(StartableSound*) ) );
    connect( ctrl,              SIGNAL( destroyed()         ),
             this,              SLOT  ( RemoveCtrl()        ) );
    connect( ctrl,              SIGNAL( SongSelected(StartableSound*) ),
             this,              SLOT  ( SetSong(StartableSound*)      ) );
    connect( ctrl,              SIGNAL( Modified()      ),
             this,              SLOT  ( UpdateList()    ) );

    SetSong(ctrl->CurrentSong());
}

void MusicCtrlPanel::SetSong(StartableSound* song)
{
    if (song == NULL)
        return;

    int songIndex = m_playlistCbo->findData(song->Title(), Qt::DisplayRole);
    if (songIndex < 0)
        throw QException("Programming Error: "
                         "Tried to set song to one not in the playlist!");

    m_playlistCbo->setCurrentIndex(songIndex);
}

void MusicCtrlPanel::OnDeleteSelected()
{
    QMessageBox::StandardButtons result =
        QMessageBox::warning(
            this,
            "Remove song",
            "Are you sure you want to remove the song from the playlist?",
            QMessageBox::Yes | QMessageBox::No );
    if (result == QMessageBox::Yes)
        delete m_playlistCbo->itemData(m_playlistCbo->currentIndex())
            .value<I_TitleCarrier*>();
}

void MusicCtrlPanel::RemoveCtrl()
{
    setEnabled(false);

    disconnect(m_musicCtrl);
    m_musicVolumeSld->disconnect(m_musicCtrl);
    m_musicMuteChk->disconnect(m_musicCtrl);

    m_musicVolumeSld->setValue(0);
    m_musicMuteChk->setChecked(false);
    m_musicCtrl = NULL;
}

void MusicCtrlPanel::ChangeSong(int index)
{
    StartableSound* selection = dynamic_cast<StartableSound*>(
        m_musicListModel->list().at(index)
        );

    emit SongSelected(selection);
}

void MusicCtrlPanel::UpdateList()
{
    const QList<A_SoundInstance*>& children = m_musicCtrl->Children();
    QList<I_TitleCarrier*> titleChildren;
    for ( QList<A_SoundInstance*>::const_iterator it = children.begin();
          it != children.end();
          it++ )
    {
        titleChildren.append(*it);
    }

    if (m_musicListModel->list() != titleChildren)
        m_musicListModel->setList(children);
}
