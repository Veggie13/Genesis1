#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "A_StreamInstance.h"


class Background : public A_StreamInstance
{
    Q_OBJECT

public:
    Background(BASS::Channel* chan, QObject* parent=NULL);
    ~Background();

    bool IsActive();
    bool IsMasterPaused();
    bool IsInstancePaused();
    int  GetMasterVolume();
    int  GetInstanceVolume();

public slots:
    bool Play();
    bool SetMasterPaused(bool pause);
    bool SetInstancePaused(bool pause);
    bool Stop();

    bool Halt(bool stopSound);
    bool Resume();

    bool SetMasterVolume(int vol);
    bool SetInstanceVolume(int vol);

signals:
    void Modified();

private:
    int  m_masterVolume;
    int  m_instanceVolume;
    bool m_masterPaused;
    bool m_instancePaused;
    bool m_active;
    bool m_halted;

};

#endif
