#include <QMessageBox>

#include "MusicCtrl.qoh"

#include "MusicCtrlPanel.qoh"


MusicCtrlPanel::MusicCtrlPanel(QWidget* parent)
:   QLabel(parent),
    m_musicCtrl(NULL)
{
    setupUi(this);
    setBackgroundRole(QPalette::Window);
    setFrameStyle(QFrame::WinPanel);
    setAutoFillBackground(true);
    setEnabled(false);

    connect( m_addBtn,      SIGNAL( clicked()           ),
             this,          SIGNAL( AddSelected()       ) );
    connect( m_deleteBtn,   SIGNAL( clicked()           ),
             this,          SLOT  ( OnDeleteSelected()  ) );
    connect( m_playlistCbo, SIGNAL( currentIndexChanged(const QString&) ),
             this,          SIGNAL( SongChanged(const QString&)         ) );
    connect( m_playlistCbo, SIGNAL( editTextChanged(const QString&)     ),
             this,          SIGNAL( SongChanged(const QString&)         ) );
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
        m_musicCtrl->disconnect(SIGNAL(destroyed(QObject*)), this);
    }

    m_musicCtrl = ctrl;
    if (!ctrl)
    {
        setEnabled(false);
        return;
    }

    setEnabled(true);
    m_playlistCbo->setModel(ctrl->Model());

    QString curSong = ctrl->CurrentSong();
    for (int i = 0; i < m_playlistCbo->count(); ++i)
    {
        if (curSong == m_playlistCbo->itemText(i))
        {
            m_playlistCbo->setCurrentIndex(i);
            break;
        }
    }
    m_musicVolumeSld->setValue(ctrl->GetVolume());
    m_musicMuteChk->setChecked(ctrl->IsMuted());

    connect( m_musicVolumeSld,  SIGNAL( valueChanged(int) ),
             ctrl,              SLOT  ( SetVolume(int)    ) );
    connect( m_musicMuteChk,    SIGNAL( toggled(bool)     ),
             ctrl,              SLOT  ( SetMuted(bool)    ) );
    connect( this,              SIGNAL( SongChanged(const QString&) ),
             ctrl,              SLOT  ( SetSong(const QString&)     ) );
    connect( this,              SIGNAL( DeleteSelected(const QString&)  ),
             ctrl,              SLOT  ( RemoveSong(const QString&)      ) );

    connect( ctrl,              SIGNAL( destroyed(QObject*) ),
             this,              SLOT  ( RemoveCtrl()        ) );
    connect( ctrl,              SIGNAL( SongSelected(const QString&) ),
             this,              SLOT  ( SetSong(const QString&)      ) );
}

void MusicCtrlPanel::SetSong(const QString& songTitle)
{
    int songIndex = m_playlistCbo->findData(songTitle, Qt::DisplayRole);
    if (songIndex < 0)
        return;

    if (m_playlistCbo->currentIndex() == songIndex)
        emit SongChanged(songTitle);
    else
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
        emit DeleteSelected(m_playlistCbo->currentText());
}

void MusicCtrlPanel::RemoveCtrl()
{
    m_musicCtrl = NULL;
    setEnabled(false);
}
