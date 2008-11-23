#include <QTimer>

#include <cmath>

#include "InstantSound.h"

#include "RandomSound.h"


RandomSound::RandomSound(InstantSound* snd, QObject* parent)
:   QObject(parent),
    m_sound(snd),
    m_period(100),
    m_variance(100),
    m_masterVolume(100),
    m_instanceVolume(100),
    m_masterPlaying(false),
    m_instancePlaying(false),
    m_active(false),
    m_halted(false),
    m_timer(NULL)
{
    if (m_sound)
        connect(m_sound, SIGNAL( destroyed() ), this, SIGNAL( ReadyForDeletion() ));

    m_timer = new QTimer;
    m_timer->setSingleShot(true);
    connect(m_timer, SIGNAL( timeout() ), this, SLOT( PlaySound() ));
}

RandomSound::~RandomSound()
{
    Stop();
    delete m_timer;
}

InstantSound* RandomSound::GetSoundObject()
{
    return m_sound;
}

void RandomSound::SetMasterInactive(bool unplay)
{
    if (m_masterPlaying == !unplay)
        return;

    m_masterPlaying = !unplay;
    emit Modified();

    if (m_halted || !m_active)
        return;
    if (m_instancePlaying && m_masterPlaying)
        m_timer->start(TimerLength());
    else if (!m_masterPlaying)
        m_timer->stop();
}

void RandomSound::SetInstanceInactive(bool unplay)
{
    if (m_instancePlaying == !unplay)
        return;

    m_instancePlaying = !unplay;
    emit Modified();

    if (m_halted || !m_active)
        return;
    if (m_instancePlaying && m_masterPlaying)
        m_timer->start(TimerLength());
    else if (!m_instancePlaying)
        m_timer->stop();
}

void RandomSound::Start()
{
    m_active = true;
    if (!m_timer->isActive() && !m_halted && m_masterPlaying && m_instancePlaying)
        m_timer->start(TimerLength());
}

void RandomSound::Stop()
{
    if (m_timer->isActive())
        m_timer->stop();

    m_active = false;
}

void RandomSound::Halt()
{
    if (m_timer->isActive())
        m_timer->stop();

    m_halted = true;
}

void RandomSound::Resume()
{
    m_halted = false;
    if (!m_timer->isActive() && m_active && m_masterPlaying && m_instancePlaying)
        m_timer->start(TimerLength());
}

bool RandomSound::IsMasterActive()
{
    return m_masterPlaying;
}

bool RandomSound::IsInstanceActive()
{
    return m_instancePlaying;
}

int RandomSound::GetPeriod()
{
    return m_period;
}

int RandomSound::GetVariance()
{
    return m_variance;
}

int RandomSound::GetMasterVolume()
{
    return m_masterVolume;
}

int RandomSound::GetInstanceVolume()
{
    return m_instanceVolume;
}

bool RandomSound::SetPeriod(int per)
{
    if (per < 0 || per > 100)
        return false;
    if (m_period == per)
        return true;

    m_period = per;
    m_timer->stop();
    m_timer->start(TimerLength());
    emit Modified();
    return true;
}

bool RandomSound::SetVariance(int var)
{
    if (var < 0 || var > 100)
        return false;
    if (m_variance == var)
        return true;

    m_variance = var;
    emit Modified();
    return true;
}

bool RandomSound::SetMasterVolume(int vol)
{
    if (vol < 0 || vol > 100)
        return false;
    if (m_masterVolume == vol)
        return true;

    m_masterVolume = vol;
    emit Modified();
    return true;
}

bool RandomSound::SetInstanceVolume(int vol)
{
    if (vol < 0 || vol > 100)
        return false;
    if (m_instanceVolume == vol)
        return true;

    m_instanceVolume = vol;
    emit Modified();
    return true;
}

void RandomSound::PlaySound()
{
    if (m_halted || !m_masterPlaying || !m_instancePlaying)
        return;

    if (m_sound)
        m_sound->Play(m_masterVolume * m_instanceVolume);

    m_timer->start(TimerLength());
}

int RandomSound::TimerLength()
{
    double lenFactor = m_period / 100.0;
    lenFactor = pow(60.0, lenFactor);

    double randFactor = std::rand() / (double)(RAND_MAX);
    randFactor *= 2.0f;
    randFactor -= 1.0f;

    double varFactor = m_variance / 100.0;

    double diffFactor = (1.8f * varFactor * asin(randFactor) / M_PI) + 1.0f;

    return (int)(diffFactor * lenFactor * 1000.0f);
}
