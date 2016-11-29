#include "A_SoundImport.qoh"

#include "StartableSound.qoh"


StartableSound::StartableSound(A_SoundImport* import, QObject* parent)
:   A_SoundInstance(import, parent)
{
}

void StartableSound::Play()
{
    Import()->Play(true);
}

void StartableSound::Stop()
{
    Import()->Stop();
}

void StartableSound::InternalSuspend()
{
    Import()->Stop();
}

void StartableSound::InternalResume()
{
}
