#include <QStringList>

#include "InstantSound.h"
#include "QStringMapRefModel.hpp"
#include "RandomSound.h"
#include "SoundMaster.h"

#include "RandomCtrl.h"


RandomCtrl::RandomCtrl(const QDomElement& random, QObject* parent)
:   QObject(parent),
    m_volume(100),
    m_muted(false),
    m_randMap(),
    m_randMapModel(&m_randMap),
    m_randMapSelModel(&m_randMapModel)
{
    if (random.isNull())
        return;

    QString vol = random.attribute("vol", "0");
    QString mute = random.attribute("mute", "0");

    SetMasterVolume(vol.toInt());
    SetMasterMuted(mute.toInt());
    for( QDomNode n = random.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement effect = n.toElement();
        if ( effect.isNull() || effect.tagName() != "effect" )
            continue;

        QString effectTitle = effect.attribute("title", "");

        AddRandom(effectTitle, effect);
    }
}

RandomCtrl::~RandomCtrl()
{
    for ( RandomMap::iterator it = m_randMap.begin();
          it != m_randMap.end();
          it++ )
    {
        it.value()->disconnect(this);
        SoundMaster::Get().ReturnInstant(it.value()->GetSoundObject());
    }
}

QAbstractItemModel* RandomCtrl::Model()
{
    return &m_randMapModel;
}

QItemSelectionModel* RandomCtrl::SelectionModel()
{
    return &m_randMapSelModel;
}

RandomSound* RandomCtrl::GetInstance(const QString& title)
{
    RandomMap::iterator finder = m_randMap.find(title);
    if (finder == m_randMap.end())
        return NULL;

    return finder.value();
}

int RandomCtrl::GetMasterVolume()
{
    return m_volume;
}

bool RandomCtrl::IsMasterMuted()
{
    return m_muted;
}

void RandomCtrl::Halt()
{
    if (m_muted)
        return;

    for ( RandomMap::iterator it = m_randMap.begin();
          it != m_randMap.end();
          it++ )
    {
        it.value()->Halt();
    }
}

void RandomCtrl::Resume()
{
    if (m_muted)
        return;

    for ( RandomMap::iterator it = m_randMap.begin();
          it != m_randMap.end();
          it++ )
    {
        it.value()->Resume();
    }
}

void RandomCtrl::WriteData(QDomElement& random)
{
    QDomDocument doc = random.ownerDocument();

    random.setAttribute("vol", QString("%1").arg( m_volume ) );
    random.setAttribute("mute", QString("%1").arg( (int)m_muted ) );
    for ( RandomMap::iterator effectIt = m_randMap.begin();
          effectIt != m_randMap.end();
          effectIt++ )
    {
        QString effectTitle = effectIt.key();
        QDomElement effect = doc.createElement("effect");
        effect.setAttribute("title", effectTitle);
        effect.setAttribute(
            "vol",
            QString("%1")
                .arg( effectIt.value()->GetInstanceVolume() ) );
        effect.setAttribute(
            "per",
            QString("%1")
                .arg( effectIt.value()->GetPeriod() ) );
        effect.setAttribute(
            "var",
            QString("%1")
                .arg( effectIt.value()->GetVariance() ) );
        effect.setAttribute(
            "mute",
            QString("%1")
                .arg( (int)!effectIt.value()->IsInstanceActive() ) );
        random.appendChild(effect);
    }
}

bool RandomCtrl::SetMasterVolume(int vol)
{
    if (vol < 0 || vol > 100)
        return false;

    m_volume = vol;

    bool retval = true;
    for ( RandomMap::iterator it = m_randMap.begin();
          it != m_randMap.end();
          it++ )
    {
        retval = it.value()->SetMasterVolume(vol) && retval;
    }

    emit Modified();
    return retval;
}

bool RandomCtrl::SetMasterMuted(bool mute)
{
    if (mute == m_muted)
        return true;

    for ( RandomMap::iterator it = m_randMap.begin();
          it != m_randMap.end();
          it++ )
    {
        it.value()->SetMasterInactive(mute);
    }

    m_muted = mute;
    emit Modified();
    return true;
}

bool RandomCtrl::AddRandom(const QString& title, const QDomElement& effect)
{
    RandomMap::iterator finder = m_randMap.find(title);
    if (finder != m_randMap.end())
        return false;

    RandomSound* newRand = new RandomSound(
        SoundMaster::Get().CreateInstant(title)
        );
    if (!newRand)
        return false;

    connect(newRand, SIGNAL( ReadyForDeletion() ), this, SLOT( RemoveDeletedRandom() ));
    connect(newRand, SIGNAL( Modified() ), this, SIGNAL( Modified() ));

    m_randMap[title] = newRand;

    newRand->Start();
    newRand->SetMasterVolume(m_volume);
    newRand->SetMasterInactive(m_muted);
    if (!effect.isNull())
    {
        QString effectVol = effect.attribute("vol", "0");
        QString effectPer = effect.attribute("per", "0");
        QString effectVar = effect.attribute("var", "0");
        QString effectMute = effect.attribute("mute", "0");

        newRand->SetInstanceVolume(effectVol.toInt());
        newRand->SetPeriod(effectPer.toInt());
        newRand->SetVariance(effectVar.toInt());
        newRand->SetInstanceInactive(effectMute.toInt());

        newRand->Halt();
    }

    emit Modified();
    return true;
}

bool RandomCtrl::RemoveRandom(const QString& title)
{
    RandomMap::iterator finder = m_randMap.find(title);
    if (finder == m_randMap.end())
        return true;

    InstantSound* doomed = finder.value()->GetSoundObject();
    if (doomed)
        SoundMaster::Get().ReturnInstant(doomed);

    return true;
}

void RandomCtrl::RemoveDeletedRandom()
{
    RandomSound* doomed = reinterpret_cast<RandomSound*>(sender());
    if (!doomed)
        return;

    RandomMap::iterator doomedIt;
    for ( doomedIt = m_randMap.begin();
          doomedIt != m_randMap.end() && doomedIt.value() != doomed;
          doomedIt++ );

    if (doomedIt != m_randMap.end())
        m_randMap.erase(doomedIt);

    emit Modified();
}
