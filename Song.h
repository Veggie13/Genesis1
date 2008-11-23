#ifndef SONG_H
#define SONG_H

#include <QTimer>

#include "A_StreamInstance.h"


class Song : public A_StreamInstance
{
    Q_OBJECT

public:
    Song(BASS::Channel* chan, QObject* parent=NULL);
    ~Song();

    bool IsActive();
    int  GetMasterVolume();

    bool StopNoSignal(bool timerOnly=false);

public slots:
    bool Play(bool restart=false);
    bool Pause();
    bool Stop();

    bool SetMasterVolume(int vol);

signals:
    void Finished();

private slots:
    void CheckCompletion();

private:
    int m_masterVolume;

    QTimer m_timer;

    static const int INTERVAL;

};

#endif
