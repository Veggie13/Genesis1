#include <bass_channel.h>

#include "InstantSound.qoh"


InstantSound::InstantSound(BASS::Channel* chan, QObject* parent)
:   QObject(parent),
    m_channel(chan)
{
}

InstantSound::~InstantSound()
{
}

double InstantSound::Length()
{
    if (!m_channel)
        return -1.0;

    return m_channel->Bytes2Seconds(m_channel->GetLength());
}

bool InstantSound::Play(int vol)
{
    if (!m_channel)
        return false;
    if (vol < 0 || vol > 10000)
        return false;

    float floatVol = vol / 10000.0f;

    try
    {
        m_channel->SetAttribute(BASS_ATTRIB_VOL, floatVol);
        m_channel->Play(true);
    }
    catch (std::exception e)
    {
        fprintf(stderr, "Channel Exception: %s\n", e.what());
        return false;
    }

    return true;
}

void InstantSound::Reassign(BASS::Channel* chan)
{
    m_channel = chan;
}
