#include "A_SoundImport.qoh"

#include "A_SoundInstance.qoh"


const int A_SoundInstance::VOLUME_MAX = 100;

A_SoundInstance::A_SoundInstance(A_SoundImport* import, QObject* parent)
:   QObject(parent),
    m_import(import),
    m_active(false),
    m_masterVolume(VOLUME_MAX),
    m_masterPaused(false),
    m_instVolume(VOLUME_MAX),
    m_instPaused(false)
{
    connect(m_import, SIGNAL( Renamed(const QString&, const QString&)   ),
            this,     SIGNAL( Renamed(const QString&, const QString&)   ) );
    connect(m_import, SIGNAL( destroyed() ), this, SIGNAL( ImportDestroyed() ));
}

const QString& A_SoundInstance::Title()
{
    return m_import->Title();
}

bool A_SoundInstance::IsActive()
{
    return m_active;
}

void A_SoundInstance::Suspend()
{
    if (!IsActive())
        return;

    disconnect(m_import, SIGNAL( SoundFinished() ), this, SIGNAL( SoundFinished() ));
    InternalSuspend();

    SetActive(false);
}

void A_SoundInstance::Resume()
{
    if (IsActive())
        return;

    InternalResume();
    connect(m_import, SIGNAL( SoundFinished() ), this, SIGNAL( SoundFinished() ));

    SetActive(true);
    UpdateImportVolume();
    UpdateImportPause();
}

int A_SoundInstance::MasterVolume()
{
    return m_masterVolume;
}

bool A_SoundInstance::IsMasterPaused()
{
    return m_masterPaused;
}

int A_SoundInstance::InstanceVolume()
{
    return m_instVolume;
}

bool A_SoundInstance::IsInstancePaused()
{
    return m_instPaused;
}

void A_SoundInstance::SetMasterVolume(int volume)
{
    if (m_masterVolume == volume)
        return;

    m_masterVolume = volume;
    UpdateImportVolume();
    emit Modified();
}

void A_SoundInstance::SetMasterPaused(bool pause)
{
    if (m_masterPaused == pause)
        return;

    m_masterPaused = pause;
    UpdateImportPause();
    emit Modified();
}

void A_SoundInstance::SetInstanceVolume(int volume)
{
    if (m_instVolume == volume)
        return;

    m_instVolume = volume;
    UpdateImportVolume();
    emit Modified();
}

void A_SoundInstance::SetInstancePaused(bool pause)
{
    if (m_instPaused == pause)
        return;

    m_instPaused = pause;
    UpdateImportPause();
    emit Modified();
}

A_SoundImport* A_SoundInstance::Import()
{
    return m_import;
}

void A_SoundInstance::SetActive(bool active)
{
    m_active = active;
}

void A_SoundInstance::UpdateImportVolume()
{
    if (!IsActive())
        return;

    double masterVol = m_masterVolume / (double)VOLUME_MAX;
    double instVol = m_instVolume / (double)VOLUME_MAX;
    Import()->SetVolume((int)(masterVol * instVol * A_SoundImport::VOLUME_MAX));
}

void A_SoundInstance::UpdateImportPause()
{
    if (IsActive())
        Import()->SetPaused(m_masterPaused || m_instPaused);
}
