#include <bass_channel.h>

#include "SoundMaster.h"
#include "Song.qoh"


const int Song::INTERVAL = 1000 /*ms*/;

Song::Song(BASS::Channel* chan, QObject* parent)
:   A_StreamInstance(chan, parent),
    m_masterVolume(100)
{
    m_timer.setInterval(INTERVAL);
    m_timer.setSingleShot(false);
    connect(&m_timer, SIGNAL( timeout() ), this, SLOT( CheckCompletion() ));
}

Song::~Song()
{
    if (!m_channel)
        return;

    try
    {
        m_channel->Stop();
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
    }
}

bool Song::Play(bool restart)
{
    if (!m_channel)
        return false;

    try
    {
        m_channel->Flags(0, BASS_SAMPLE_LOOP);
        m_channel->Play(restart);
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    m_timer.start();
    return SetMasterVolume(m_masterVolume);
}

bool Song::Pause()
{
    if (!m_channel)
        return false;

    try
    {
        m_channel->Pause();
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    return true;
}

bool Song::Stop()
{
    if (!m_channel)
        return false;

    try
    {
        if (m_channel->GetActiveState() != BASS::STOPPED)
        {
            m_channel->Stop();
            m_timer.stop();
            emit Finished();
        }
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    return true;
}

bool Song::StopNoSignal(bool timerOnly)
{
    m_timer.stop();
    if (timerOnly)
        return true;

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

    return true;
}

bool Song::IsActive()
{
    if (!m_channel)
        return false;

    bool result;
    try
    {
        result = m_channel->GetActiveState() != BASS::STOPPED;
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    return result;
}

void Song::CheckCompletion()
{
    if (!IsActive())
    {
        m_timer.stop();
        emit Finished();
    }
}

bool Song::SetMasterVolume(int vol)
{
    if (!m_channel)
        return false;
    if (vol < 0 || vol > 100)
        return false;

    float floatVol = vol / 100.0f;

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
    return true;
}

int Song::GetMasterVolume()
{
    if (!m_channel)
        return -1;

    return m_masterVolume;
}
