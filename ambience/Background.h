#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "A_SoundInstance.qoh"


class Background : public A_SoundInstance
{
public:
    Background(A_SoundImport* import, QObject* parent=NULL);

protected:
    virtual void InternalSuspend();
    virtual void InternalResume();

};

#endif
