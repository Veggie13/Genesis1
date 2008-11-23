#include <QTimer>

#include <bass_channel.h>

#include "SoundMaster.h"
#include "Background.h"


Background::Background(BASS::Channel* chan, QObject* parent)
:   A_StreamInstance(chan, parent),
    m_masterVolume(100),
    m_instanceVolume(100),
    m_masterPaused(false),
    m_instancePaused(false),
    m_active(false),
    m_halted(false)
{
}

Background::~Background()
{
    Stop();
}

bool Background::Play()
{
    if (!m_channel)
        return false;

    try
    {
        m_channel->Flags(BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
        m_channel->Play(false);
        if (m_halted)
            m_channel->Pause();
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    m_masterPaused = false;
    m_instancePaused = false;
    m_active = true;
    return true;
}

bool Background::SetMasterPaused(bool pause)
{
    if (!m_channel)
        return false;

    if ( (m_instancePaused || m_masterPaused) ==
         (m_instancePaused || pause) )
    {
        if (m_masterPaused != pause)
        {
            m_masterPaused = pause;
            emit Modified();
        }
        return true;
    }

    if (!m_halted && m_active)
    {
        try
        {
            if (pause)
                m_channel->Pause();
            else
                m_channel->Play();
        }
        catch (std::exception e)
        {
            fprintf(stderr, "Channel Exception: %s\n", e.what());
            return false;
        }
    }

    m_masterPaused = pause;
    emit Modified();
    return true;
}

bool Background::SetInstancePaused(bool pause)
{
    if (!m_channel)
        return false;

    if ( (m_masterPaused || m_instancePaused) ==
         (m_masterPaused || pause) )
    {
        if (m_instancePaused != pause)
        {
            m_instancePaused = pause;
            emit Modified();
        }
        return true;
    }

    if (!m_halted && m_active)
    {
        try
        {
            if (pause)
                m_channel->Pause();
            else
                m_channel->Play();
        }
        catch (std::exception e)
        {
            fprintf(stderr, "Channel Exception: %s\n", e.what());
            return false;
        }
    }

    m_instancePaused = pause;
    emit Modified();
    return true;
}

bool Background::Stop()
{
    if (!m_channel)
        return false;

    try
    {
        m_channel->Stop();
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    m_masterPaused = false;
    m_instancePaused = false;
    m_active = false;
    return true;
}

bool Background::Halt(bool stopMusic)
{
    if (!m_channel)
        return false;

    if (m_halted)
        return true;

    if (stopMusic && IsActive() && !m_masterPaused && !m_instancePaused)
    {
        try
        {
            m_channel->Pause();
        }
        catch (std::exception e)
        {
            fprintf(stderr, "Channel Exception: %s\n", e.what());
            return false;
        }
    }

    m_halted = true;
    return true;
}

bool Background::Resume()
{
    if (!m_channel)
        return false;

    if (!m_halted)
        return true;

    if (m_active)
    {
        try
        {
            m_channel->Play();
            m_channel->SetAttribute(BASS_ATTRIB_VOL, m_masterVolume*m_instanceVolume/10000.0f);
            if (m_masterPaused || m_instancePaused)
                m_channel->Pause();
        }
        catch (std::exception e)
        {
            fprintf(stderr, "Channel Exception: %s\n", e.what());
            return false;
        }
    }
    else
    {
        try
        {
            m_channel->Stop();
        }
        catch (std::exception e)
        {
            fprintf(stderr, "Channel Exception: %s\n", e.what());
            return false;
        }
    }

    m_halted = false;
    return true;
}

bool Background::IsActive()
{
    if (!m_channel)
        return false;

    bool result;
    try
    {
        result = !(m_channel->GetActiveState() == BASS::STOPPED);
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    return result;
}

bool Background::IsMasterPaused()
{
    return m_masterPaused;
}

bool Background::IsInstancePaused()
{
    return m_instancePaused;
}

bool Background::SetMasterVolume(int vol)
{
    if (!m_channel)
        return false;
    if (vol < 0 || vol > 100)
        return false;
    if (m_masterVolume == vol)
        return true;

    float floatVol = (vol * m_instanceVolume) / 10000.0f;

    try
    {
        m_channel->SetAttribute(BASS_ATTRIB_VOL, floatVol);
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    m_masterVolume = vol;
    emit Modified();
    return true;
}

bool Background::SetInstanceVolume(int vol)
{
    if (!m_channel)
        return false;
    if (vol < 0 || vol > 100)
        return false;
    if (m_instanceVolume == vol)
        return true;

    float floatVol = (vol * m_masterVolume) / 10000.0f;

    try
    {
        m_channel->SetAttribute(BASS_ATTRIB_VOL, floatVol);
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    m_instanceVolume = vol;
    emit Modified();
    return true;
}

int Background::GetMasterVolume()
{
    if (!m_channel)
        return -1;

    return m_masterVolume;
}

int Background::GetInstanceVolume()
{
    if (!m_channel)
        return -1;

    return m_instanceVolume;
}
