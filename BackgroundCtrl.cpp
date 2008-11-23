#include <QStringList>

#include "Background.h"
#include "SoundMaster.h"

#include "BackgroundCtrl.h"


BackgroundCtrl::BackgroundCtrl(const QDomElement& background, QObject* parent)
:   QObject(parent),
    m_volume(100),
    m_muted(false),
    m_bgMap(),
    m_bgMapModel(&m_bgMap),
    m_bgMapSelModel(&m_bgMapModel)
{
    if (background.isNull())
        return;

    QString vol = background.attribute("vol", "0");
    QString mute = background.attribute("mute", "0");

    SetMasterVolume(vol.toInt());
    SetMasterMuted(mute.toInt());
    for( QDomNode n = background.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement sound = n.toElement();
        if ( sound.isNull() || sound.tagName() != "sound" )
            continue;

        QString soundTitle = sound.attribute("title", "");

        AddBackground(soundTitle, sound);
    }
}

BackgroundCtrl::~BackgroundCtrl()
{
    for ( BackgroundMap::iterator it = m_bgMap.begin();
          it != m_bgMap.end();
          it++ )
    {
        it.value()->disconnect(this);
        SoundMaster::Get().ReturnBackground(it.value());
    }
}

QAbstractItemModel* BackgroundCtrl::Model()
{
    return &m_bgMapModel;
}

QItemSelectionModel* BackgroundCtrl::SelectionModel()
{
    return &m_bgMapSelModel;
}

Background* BackgroundCtrl::GetInstance(const QString& title)
{
    BackgroundMap::iterator finder = m_bgMap.find(title);
    if (finder == m_bgMap.end())
        return NULL;

    return finder.value();
}

QStringList BackgroundCtrl::SharedWith(const BackgroundCtrl& other)
{
    QStringList retList;

    for ( BackgroundMap::iterator it = m_bgMap.begin();
          it != m_bgMap.end();
          it++ )
    {
        BackgroundMap::const_iterator finder = other.m_bgMap.find(it.key());
        if (finder != other.m_bgMap.end())
            retList.append(it.key());
    }

    return retList;
}

int BackgroundCtrl::GetMasterVolume()
{
    return m_volume;
}

bool BackgroundCtrl::IsMasterMuted()
{
    return m_muted;
}

bool BackgroundCtrl::Halt(const QStringList& exceptions)
{
    bool retval = true;
    for ( BackgroundMap::iterator it = m_bgMap.begin();
          it != m_bgMap.end();
          it++ )
    {
        Background* bg = it.value();
        retval = bg->Halt(!exceptions.contains(it.key())) && retval;
    }

    return retval;
}

bool BackgroundCtrl::Resume()
{
    bool retval = true;
    for ( BackgroundMap::iterator it = m_bgMap.begin();
          it != m_bgMap.end();
          it++ )
    {
        Background* bg = it.value();
        retval = bg->Resume() && retval;
    }

    return retval;
}

void BackgroundCtrl::WriteData(QDomElement& background)
{
    QDomDocument doc = background.ownerDocument();

    background.setAttribute("vol", QString("%1").arg( m_volume ) );
    background.setAttribute("mute", QString("%1").arg( (int)m_muted ) );
    for ( BackgroundMap::iterator soundIt = m_bgMap.begin();
          soundIt != m_bgMap.end();
          soundIt++ )
    {
        QString soundTitle = soundIt.key();
        QDomElement sound = doc.createElement("sound");
        sound.setAttribute("title", soundTitle);
        sound.setAttribute(
            "vol",
            QString("%1").arg( soundIt.value()->GetInstanceVolume() ) );
        sound.setAttribute(
            "mute",
            QString("%1").arg( (int)soundIt.value()->IsInstancePaused() ) );
        background.appendChild(sound);
    }
}

bool BackgroundCtrl::SetMasterVolume(int vol)
{
    if (vol < 0 || vol > 100)
        return false;

    m_volume = vol;

    bool retval = true;
    for ( BackgroundMap::iterator it = m_bgMap.begin();
          it != m_bgMap.end();
          it++ )
    {
        retval = it.value()->SetMasterVolume(vol) && retval;
    }

    emit Modified();
    return retval;
}

bool BackgroundCtrl::SetMasterMuted(bool mute)
{
    m_muted = mute;

    bool retval = true;
    for ( BackgroundMap::iterator it = m_bgMap.begin();
          it != m_bgMap.end();
          it++ )
    {
        retval = it.value()->SetMasterPaused(m_muted) && retval;
    }

    emit Modified();
    return retval;
}

bool BackgroundCtrl::AddBackground(const QString& title, const QDomElement& sound)
{
    BackgroundMap::iterator finder = m_bgMap.find(title);
    if (finder != m_bgMap.end())
        return false;

    Background* newBg = SoundMaster::Get().CreateBackground(title);
    if (!newBg)
        return false;

    connect(newBg, SIGNAL( destroyed() ), this, SLOT( RemoveDeletedBackground() ));
    connect(newBg, SIGNAL( Modified() ), this, SIGNAL( Modified() ));

    m_bgMap[title] = newBg;

    newBg->Play();
    newBg->SetMasterVolume(m_volume);
    newBg->SetMasterPaused(m_muted);
    if (!sound.isNull())
    {
        QString soundVol = sound.attribute("vol", "0");
        QString soundMute = sound.attribute("mute", "0");

        newBg->SetInstanceVolume(soundVol.toInt());
        newBg->SetInstancePaused(soundMute.toInt());

        newBg->Halt(true);
    }

    emit Modified();
    return true;
}

bool BackgroundCtrl::RemoveBackground(const QString& title)
{
    BackgroundMap::iterator finder = m_bgMap.find(title);
    if (finder == m_bgMap.end())
        return true;

    Background* doomed = finder.value();
    if (doomed)
        SoundMaster::Get().ReturnBackground(doomed);

    return true;
}

void BackgroundCtrl::RemoveDeletedBackground()
{
    Background* doomed = reinterpret_cast<Background*>(sender());
    if (!doomed)
        return;

    BackgroundMap::iterator doomedIt;
    for ( doomedIt = m_bgMap.begin();
          doomedIt != m_bgMap.end() && doomedIt.value() != doomed;
          doomedIt++ );

    if (doomedIt != m_bgMap.end())
        m_bgMap.erase(doomedIt);

    emit Modified();
}
