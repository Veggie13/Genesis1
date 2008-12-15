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

    double GetPeriod();
    int GetPeriodType();
    int GetVariance();
    int GetMasterVolume();
    int GetInstanceVolume();

signals:
    void Modified();
    void ReadyForDeletion();

public slots:
    bool SetPeriod(double per);
    bool SetPeriodType(int type);
    bool SetVariance(int var);
    bool SetMasterVolume(int vol);
    bool SetInstanceVolume(int vol);

    void SetMasterInactive(bool unplay);
    void SetInstanceInactive(bool unplay);

protected slots:
    void PlaySound();

private:
    bool IsPeriodValid(double per);
    int TimerLength();


    InstantSound* m_sound;

    double m_period;
    int m_periodType;
    int m_variance;
    int m_masterVolume;
    int m_instanceVolume;

    bool m_masterPlaying;
    bool m_instancePlaying;
    bool m_active;
    bool m_halted;

    QTimer* m_timer;


    static const int PERIOD_TYPE_MULT;
    static const int PERIOD_TYPE_TIME;

};

#endif
