#include "A_SoundImport.qoh"

#include "Background.h"


Background::Background(A_SoundImport* import, QObject* parent)
:   A_SoundInstance(import, parent)
{
}

void Background::InternalSuspend()
{
    Import()->Stop();
}

void Background::InternalResume()
{
    Import()->Play(true, true);
}
