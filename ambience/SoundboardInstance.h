#ifndef SOUNDBOARDINSTANCE_H
#define SOUNDBOARDINSTANCE_H

#include "StartableSound.qoh"


class SoundboardInstance : public StartableSound
{
public:
    SoundboardInstance(A_SoundImport* import, QObject* parent = NULL);

public slots:
    virtual void Play();

protected:
    virtual void UpdateImportVolume();

};

#endif
