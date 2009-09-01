#include <QTimer>

#include <cmath>

#include "A_SoundImport.qoh"
#include "QException.h"

#include "RandomSound.qoh"


#define DOUBLES_EQUAL(x, y)  ( ((x)-(y)) * ((x)-(y)) < (1.0e-10) )


const RandomSound::PeriodType RandomSound::PeriodTypes[] = {MULT, TIME};

RandomSound::RandomSound(A_SoundImport* import, QObject* parent)
:   A_SoundInstance(import, parent),
    m_period(100.0),
    m_periodType(MULT),
    m_variance(100),
    m_timer(NULL)
{
    m_timer = new QTimer;
    m_timer->setSingleShot(true);
    connect(m_timer, SIGNAL( timeout() ), this, SLOT( PlaySound() ));
}

RandomSound::~RandomSound()
{
    delete m_timer;
}

void RandomSound::InternalSuspend()
{
    if (m_timer->isActive())
        m_timer->stop();

    Import()->Stop();
}

void RandomSound::InternalResume()
{
}

void RandomSound::UpdateImportVolume()
{
    // we don't update the import for RandomSound; we do it before we play
}

void RandomSound::UpdateImportPause()
{
    // we don't update the import for RandomSound; pausing applies to the timer
    if (!IsMasterPaused() && !IsInstancePaused())
        m_timer->start(TimerLength());
    else if (m_timer->isActive())
        m_timer->stop();
}

double RandomSound::Period()
{
    return m_period;
}

RandomSound::PeriodType RandomSound::GetPeriodType()
{
    return m_periodType;
}

int RandomSound::Variance()
{
    return m_variance;
}

void RandomSound::SetPeriod(double per)
{
    if (!IsPeriodValid(per))
        throw QException("Programming Error: "
                         "Tried to set Period outside of valid range!");
    if (DOUBLES_EQUAL(m_period, per))
        return;

    m_period = per;
    if (m_timer->isActive())
    {
        m_timer->stop();
        m_timer->start(TimerLength());
    }
    emit Modified();
}

void RandomSound::SetPeriodType(RandomSound::PeriodType type)
{
    if (m_periodType == type)
        return;

    m_periodType = type;
    if (!IsPeriodValid(m_period))
        m_period = 1.0;

    if (m_timer->isActive())
    {
        m_timer->stop();
        m_timer->start(TimerLength());
    }
    emit Modified();
}

void RandomSound::SetVariance(int var)
{
    if (var < 0 || var > 100)
        throw QException("Programming Error: "
                         "Tried to set variance outside of valid range!");
    if (m_variance == var)
        return;

    m_variance = var;
    emit Modified();
}

void RandomSound::PlaySound()
{
    A_SoundInstance::UpdateImportVolume();
    Import()->Play(true);
    m_timer->start(TimerLength());
}

bool RandomSound::IsPeriodValid(double per)
{
    return (per >= 1.0 && per <= 100.0);
}

int RandomSound::TimerLength()
{
    double lenFactor = m_period;

    double randFactor = std::rand() / (double)(RAND_MAX);
    randFactor *= 2.0f;
    randFactor -= 1.0f;

    double varFactor = m_variance / 100.0;

    double diffFactor = (1.8f * varFactor * asin(randFactor) / M_PI) + 1.0f;

    double result = diffFactor * lenFactor;
    double soundLength = Import()->Length();
    if (m_periodType == MULT)
        result *= soundLength;

    if (result < soundLength)
        result = soundLength;

    return (int)(result * 1000.0f);
}
