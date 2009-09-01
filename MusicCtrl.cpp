#include <cmath>

#include "QException.h"
#include "StartableSound.qoh"

#include "MusicCtrl.qoh"


MusicCtrl::MusicCtrl(QObject* parent)
:   MasterCtrl(parent),
    m_curSong(NULL)
{
}

bool MusicCtrl::SharesCurrentSongWith(const MusicCtrl& other)
{
    if (m_curSong == NULL)
        return false;

    return (other.m_instanceList.lastIndexOf(m_curSong) != -1);
}

StartableSound* MusicCtrl::CurrentSong()
{
    return m_curSong;
}

void MusicCtrl::InternalResume()
{
    SelectRandomSong();
}

void MusicCtrl::SetCurrentSong(StartableSound* song)
{
    if (song == m_curSong)
        return;

    if (song == NULL)
    {
        if (m_curSong != NULL)
            m_curSong->Stop();
        m_curSong = song;
        return;
    }

    int index = m_instanceList.lastIndexOf(song);
    if (index == -1)
        throw QException("Programming Error: "
                         "Tried to set the song to something not in the list!");

    if (m_curSong != NULL)
        m_curSong->Stop();

    m_curSong = song;
    m_curSong->Play();
    emit SongSelected(m_curSong);
}

void MusicCtrl::InternalAddInstance(A_SoundInstance* newSound)
{
    StartableSound* newSong = dynamic_cast<StartableSound*>(newSound);
    if (newSong == NULL)
        throw QException("Programming Error: "
                         "Trying to add non-song to the Music control!");

    connect(newSong, SIGNAL( SoundFinished() ), this, SLOT( SelectRandomSong() ));

    if (IsActive() && m_instanceList.count() == 1)
        SelectRandomSong();
}

void MusicCtrl::SelectRandomSong()
{
    A_SoundInstance* newChoice = m_curSong;
    if (m_instanceList.count() > 1)
    {
        while (newChoice == m_curSong)
        {
            int n = std::rand() % m_instanceList.count();
            newChoice = m_instanceList.at(n);
        }
    }
    else if (m_instanceList.count() == 1)
    {
        newChoice = m_instanceList.at(0);
    }

    StartableSound* newSong = dynamic_cast<StartableSound*>(newChoice);
    SetCurrentSong(newSong);
}

void MusicCtrl::InternalRemoveDeletedInstance(A_SoundInstance* doomed)
{
    if (m_curSong == doomed)
        SelectRandomSong();
}
