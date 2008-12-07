#include <cmath>

#include "QStringMapRefModel.hpp"
#include "Song.h"
#include "SoundMaster.h"

#include "MusicCtrl.h"


MusicCtrl::MusicCtrl(const QDomElement& music, QObject* parent)
:   QObject(parent),
    m_volume(100),
    m_muted(false),
    m_songMap(),
    m_songMapModel(&m_songMap),
    m_songMapSelModel(&m_songMapModel),
    m_curSong(m_songMap.end())
{
    if (music.isNull())
        return;

    QString vol = music.attribute("vol", "0");
    QString mute = music.attribute("mute", "0");

    SetVolume(vol.toInt());
    SetMuted(mute.toInt());
    for( QDomNode n = music.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement song = n.toElement();
        if ( song.isNull() || song.tagName() != "song" )
            continue;

        QString songTitle = song.attribute("title", "");
        AddSong(songTitle);
    }
}

MusicCtrl::~MusicCtrl()
{
    for ( SongMap::iterator it = m_songMap.begin();
          it != m_songMap.end();
          it++ )
    {
        it.value()->disconnect(this);
        SoundMaster::Get().ReturnSong(it.value());
    }
}

QAbstractItemModel* MusicCtrl::Model()
{
    return &m_songMapModel;
}

QItemSelectionModel* MusicCtrl::SelectionModel()
{
    return & m_songMapSelModel;
}

bool MusicCtrl::SharesCurrentSongWith(const MusicCtrl& other)
{
    if (m_curSong == m_songMap.end())
        return false;

    return (other.m_songMap.find(m_curSong.key()) != other.m_songMap.end());
}

QString MusicCtrl::CurrentSong()
{
    if (m_curSong == m_songMap.end())
        return "";

    return m_curSong.key();
}

int MusicCtrl::GetVolume()
{
    return m_volume;
}

bool MusicCtrl::IsMuted()
{
    return m_muted;
}

bool MusicCtrl::Halt(bool keepCurrent)
{
    if (m_curSong == m_songMap.end())
        return true;

    bool retval = m_curSong.value()->StopNoSignal(keepCurrent);
    m_curSong = m_songMap.end();
    return retval;
}

void MusicCtrl::Resume(bool useSpecific, const QString& title)
{
    if (useSpecific)
        emit SongSelected(title);
    else
        SelectRandomSong();
}

void MusicCtrl::WriteData(QDomElement& music)
{
    QDomDocument doc = music.ownerDocument();

    music.setAttribute("vol", QString("%1").arg( m_volume ) );
    music.setAttribute("mute", QString("%1").arg( (int)m_muted ) );
    for ( SongMap::iterator songIt = m_songMap.begin();
          songIt != m_songMap.end();
          songIt++ )
    {
        QString songTitle = songIt.key();
        QDomElement song = doc.createElement("song");
        song.setAttribute("title", songTitle);
        music.appendChild(song);
    }
}

bool MusicCtrl::SetVolume(int vol)
{
    if (vol < 0 || vol > 100)
        return false;

    if ( m_curSong != m_songMap.end() &&
         !m_curSong.value()->SetMasterVolume(vol) )
        return false;

    m_volume = vol;
    emit Modified();
    return true;
}

bool MusicCtrl::SetMuted(bool mute)
{
    if (m_curSong != m_songMap.end())
    {
        if (mute)
        {
            if (!m_curSong.value()->Pause())
                return false;
        }
        else
        {
            if (!m_curSong.value()->Play())
                return false;
        }
    }

    m_muted = mute;
    emit Modified();
    return true;
}

bool MusicCtrl::SetSong(const QString& title)
{
    if (title == "")
        return true;

    SongMap::iterator finder = m_songMap.find(title);
    if (finder == m_songMap.end())
        return false;
    if (finder == m_curSong && m_curSong.value()->IsActive())
        return true;

    if (m_curSong != m_songMap.end() && !m_curSong.value()->Stop())
        return false;

    m_curSong = finder;
    if (!m_curSong.value()->Play())
        return false;

    return (m_curSong.value()->SetMasterVolume(m_volume)) &&
           (!m_muted || m_curSong.value()->Pause());
}

bool MusicCtrl::AddSong(const QString& title)
{
    SongMap::iterator finder = m_songMap.find(title);
    if (finder != m_songMap.end())
        return false;

    Song* newSong = SoundMaster::Get().CreateSong(title);
    if (!newSong)
        return false;

    connect(newSong, SIGNAL( Finished()  ), this, SLOT( SelectRandomSong() ));
    connect(newSong, SIGNAL( destroyed() ), this, SLOT( RemoveDeletedSong()  ));

    m_songMap[title] = newSong;
    if (m_songMap.count() == 1)
        SelectRandomSong();
    else
        emit SongSelected(CurrentSong());

    emit Modified();
    return true;
}

bool MusicCtrl::RemoveSong(const QString& title)
{
    SongMap::iterator finder = m_songMap.find(title);
    if (finder == m_songMap.end())
        return true;

    Song* doomed = finder.value();
    if (doomed)
        SoundMaster::Get().ReturnSong(doomed);

    return true;
}

void MusicCtrl::RenameSong(const QString& title, const QString& newTitle)
{
    SongMap::iterator finder = m_songMap.find(title);
    if (finder == m_songMap.end())
        return;

    Song* renamed = finder.value();
    SongMap::iterator newEntry = m_songMap.insert(newTitle, renamed);
    bool cond = (finder == m_curSong);
    m_songMap.erase(finder);
    if (cond)
    {
        m_curSong = newEntry;
        emit SongSelected(newTitle);
    }
}

void MusicCtrl::SelectRandomSong()
{
    SongMap::iterator newIndex = m_curSong;
    if (m_songMap.count() > 1)
    {
        while (newIndex == m_curSong)
        {
            int n = std::rand() % m_songMap.count();
            int i;
            for ( newIndex = m_songMap.begin(), i = 0;
                  i < n;
                  newIndex++, ++i );
        }
    }
    else if (m_songMap.count() == 1)
    {
        newIndex = m_songMap.begin();
    }

    if (newIndex != m_songMap.end())
        emit SongSelected(newIndex.key());
}

void MusicCtrl::RemoveDeletedSong()
{
    Song* doomed = reinterpret_cast<Song*>(sender());
    if (!doomed)
        return;

    if (m_curSong != m_songMap.end() && m_curSong.value() == doomed)
    {
        m_songMap.erase(m_curSong);
        m_curSong = m_songMap.end();
        SelectRandomSong();
    }
    else
    {
        SongMap::iterator doomedIt;
        for ( doomedIt = m_songMap.begin();
              doomedIt != m_songMap.end() && doomedIt.value() != doomed;
              doomedIt++ );

        if (doomedIt != m_songMap.end())
            m_songMap.erase(doomedIt);
    }

    emit Modified();
}
