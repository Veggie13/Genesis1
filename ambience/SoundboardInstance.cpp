#include "SoundboardInstance.h"


SoundboardInstance::SoundboardInstance(A_SoundImport* import, QObject* parent)
:   StartableSound(import, parent)
{
}

void SoundboardInstance::Play()
{
    StartableSound::UpdateImportVolume();
    StartableSound::Play();
}

void SoundboardInstance::UpdateImportVolume()
{
    // do nothing to the import here; do it before playing
}
