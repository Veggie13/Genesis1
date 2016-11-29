#include "A_SoundInstance.qoh"
#include "QException.h"

#include "MasterCtrl.qoh"


MasterCtrl::MasterCtrl(QObject* parent)
:   QObject(parent),
    m_instanceList(),
    m_volume(100),
    m_paused(false),
    m_active(false)
{
}

MasterCtrl::~MasterCtrl()
{
    for ( QList<A_SoundInstance*>::iterator it = m_instanceList.begin();
          it != m_instanceList.end();
          it++ )
    {
        (*it)->disconnect(this);
        delete (*it);
    }
}

const QList<A_SoundInstance*>& MasterCtrl::Children()
{
    return m_instanceList;
}

QList<A_SoundInstance*> MasterCtrl::SharedWith(const MasterCtrl& other)
{
    QList<A_SoundInstance*> retList;

    for ( QList<A_SoundInstance*>::iterator it = m_instanceList.begin();
          it != m_instanceList.end();
          it++ )
    {
        int index = other.m_instanceList.lastIndexOf(*it);
        if (index != -1)
            retList.append(*it);
    }

    return retList;
}

int MasterCtrl::Volume()
{
    return m_volume;
}

bool MasterCtrl::IsPaused()
{
    return m_paused;
}

void MasterCtrl::Suspend()
{
    if (!IsActive())
        return;

    for ( QList<A_SoundInstance*>::iterator it = m_instanceList.begin();
          it != m_instanceList.end();
          it++ )
    {
        (*it)->Suspend();
    }

    InternalSuspend();

    m_active = false;
}

void MasterCtrl::Resume()
{
    if (IsActive())
        return;

    for ( QList<A_SoundInstance*>::iterator it = m_instanceList.begin();
          it != m_instanceList.end();
          it++ )
    {
        (*it)->Resume();
    }

    InternalResume();

    m_active = true;
}

bool MasterCtrl::IsActive()
{
    return m_active;
}

void MasterCtrl::SetVolume(int vol)
{
    if (vol < 0 || vol > 100)
        throw QException("Programming Error: "
                         "Tried to set volume outside valid range!");

    m_volume = vol;
    emit MasterVolumeChanged(m_volume);
    emit Modified();
}

void MasterCtrl::SetPaused(bool pause)
{
    if (m_paused == pause)
        return;

    m_paused = pause;
    emit MasterPauseToggled(pause);
    emit Modified();
}

void MasterCtrl::AddInstance(A_SoundInstance* newSound)
{
    if (newSound == NULL)
        throw QException("Programming Error: "
                         "Tried to add NULL Instance to Master!");

    int index = m_instanceList.lastIndexOf(newSound);
    if (index != -1)
        throw QException("Programming Error: "
                         "Tried to add Instance to Master that was already there!");

    connect(newSound, SIGNAL( destroyed() ), this, SLOT( RemoveDeletedInstance() ));

    connect( this,      SIGNAL( MasterVolumeChanged(int)    ),
             newSound,  SLOT  ( SetMasterVolume(int)        ) );
    connect( this,      SIGNAL( MasterPauseToggled(bool)    ),
             newSound,  SLOT  ( SetMasterPaused(bool)       ) );

    m_instanceList.append(newSound);
    emit ChildListChanged();

    newSound->SetMasterVolume(m_volume);
    newSound->SetMasterPaused(m_paused);
    InternalAddInstance(newSound);
    emit Modified();
}

void MasterCtrl::RemoveDeletedInstance()
{
    A_SoundInstance* doomed = reinterpret_cast<A_SoundInstance*>(sender());
    if (doomed == NULL)
        return;

    int index = m_instanceList.lastIndexOf(doomed);
    if (index == -1)
        return;

    m_instanceList.removeAt(index);
    emit ChildListChanged();
    InternalRemoveDeletedInstance(doomed);
    emit Modified();
}

void MasterCtrl::InternalSuspend()
{
}

void MasterCtrl::InternalResume()
{
}

void MasterCtrl::InternalAddInstance(A_SoundInstance* newSound)
{
}

void MasterCtrl::InternalRemoveDeletedInstance(A_SoundInstance* doomed)
{
}
