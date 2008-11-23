#ifndef RANDOMSOUND_H
#define RANDOMSOUND_H

#include <QObject>

class InstantSound;
class QTimer;


class RandomSound : public QObject
{
    Q_OBJECT

public:
    RandomSound(InstantSound* snd, QObject* parent=NULL);
    ~RandomSound();

    InstantSound* GetSoundObject();

    void Start();
    void Stop();

    void Halt();
    void Resume();

    bool IsMasterActive();
    bool IsInstanceActive();

    int GetPeriod();
    int GetVariance();
    int GetMasterVolume();
    int GetInstanceVolume();

signals:
    void Modified();
    void ReadyForDeletion();

public slots:
    bool SetPeriod(int per);
    bool SetVariance(int var);
    bool SetMasterVolume(int vol);
    bool SetInstanceVolume(int vol);

    void SetMasterInactive(bool unplay);
    void SetInstanceInactive(bool unplay);

protected slots:
    void PlaySound();

private:
    int TimerLength();


    InstantSound* m_sound;

    int m_period;
    int m_variance;
    int m_masterVolume;
    int m_instanceVolume;

    bool m_masterPlaying;
    bool m_instancePlaying;
    bool m_active;
    bool m_halted;

    QTimer* m_timer;

};

#endif
