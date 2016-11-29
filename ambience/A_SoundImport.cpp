#include <QTimer>

#include <bass_channel.h>
#include <bass_exception.h>

#include "QException.h"

#include "A_SoundImport.qoh"


const int A_SoundImport::VOLUME_MAX = 100;
const int A_SoundImport::INTERVAL = 1000 /*ms*/;

A_SoundImport::A_SoundImport(
    const QString& title,
    const QString& filename,
    QObject* parent )
:   QObject(parent),
    m_title(title),
    m_filename(filename),
    m_channel(NULL),
    m_paused(false),
    m_volume(VOLUME_MAX),
    m_playState(STOPPED),
    m_timer(NULL),
    m_initialized(false),
    m_looping(-1)
{
}

A_SoundImport::~A_SoundImport()
{
    if (!m_initialized)
        return;

    emit AboutToDie();

    delete m_timer;
    delete m_channel;
}

const QString& A_SoundImport::Title()
{
    return m_title;
}

void A_SoundImport::SetTitle(const QString& newTitle)
{
    if (!m_initialized)
        throw QException("Programming Error: "
                         "Operation on Import before it's initialized!");

    QString oldTitle = m_title;
    m_title = newTitle;

    emit Renamed(oldTitle, newTitle);
    emit Modified();
}

const QString& A_SoundImport::Filename()
{
    return m_filename;
}

void A_SoundImport::ReimportFrom(const QString& newFilename)
{
    if (!m_initialized)
        throw QException("Programming Error: "
                         "Operation on Import before it's initialized!");

    QString oldFilename = m_filename;
    m_filename = newFilename;
    delete m_channel;
    Import();

    emit Reimported(oldFilename, newFilename);
    emit Modified();
}

void A_SoundImport::Play(bool restart, bool loop)
{
    if (!m_initialized)
        throw QException("Programming Error: "
                         "Operation on Import before it's initialized!");

    if (m_playState != STOPPED)
        return;

    try
    {
        if ( ((int)loop) != m_looping )
        {
            m_channel->Flags(
                loop ? BASS_SAMPLE_LOOP : 0,
                BASS_SAMPLE_LOOP );
            m_looping = ((int)loop);
        }
        m_channel->Play(restart);
        m_playState = PLAYING;
    }
    catch (const BASS::Exception& ex)
    {
        throw QException(QString("BASS Exception: ") + ex.what());
    }
    SetChannelVolume();
    SetChannelPause(restart);

    if (!loop)
        m_timer->start(INTERVAL);
}

void A_SoundImport::SetPaused(bool pause)
{
    if (!m_initialized)
        throw QException("Programming Error: "
                         "Operation on Import before it's initialized!");

    if (m_paused == pause)
        return;

    m_paused = pause;
    emit Modified();
    if (m_playState != STOPPED)
        SetChannelPause(false);
}

void A_SoundImport::Stop()
{
    if (!m_initialized)
        throw QException("Programming Error: "
                         "Operation on Import before it's initialized!");

    if (m_playState == STOPPED)
        return;

    try
    {
        m_channel->Stop();
    }
    catch (const BASS::Exception& ex)
    {
        throw QException(QString("BASS Exception: ") + ex.what());
    }

    m_timer->stop();
    m_playState = STOPPED;
}

void A_SoundImport::SetVolume(int volume)
{
    if (!m_initialized)
        throw QException("Programming Error: "
                         "Operation on Import before it's initialized!");

    if (m_volume == volume)
        return;

    m_volume = volume;
    emit Modified();
    if (m_playState != STOPPED)
        SetChannelVolume();
}

A_SoundImport::PlayState A_SoundImport::GetPlayState()
{
    return m_playState;
}

double A_SoundImport::Length()
{
    if (!m_initialized)
        throw QException("Programming Error: "
                         "Operation on Import before it's initialized!");

    try
    {
        return m_channel->Bytes2Seconds(m_channel->GetLength());
    }
    catch (const BASS::Exception& ex)
    {
        throw QException(QString("BASS Exception: ") + ex.what());
    }
}

BASS::Channel* A_SoundImport::GetChannel()
{
    return m_channel;
}

void A_SoundImport::SetChannel(BASS::Channel* channel)
{
    m_channel = channel;
}

void A_SoundImport::Initialize()
{
    if (m_initialized)
        return;

    Import();
    m_timer = new QTimer;
    connect(m_timer, SIGNAL( timeout() ), this, SLOT( CheckCompletion() ));
    m_initialized = true;
}

void A_SoundImport::CheckCompletion()
{
    try
    {
        if (m_channel->GetActiveState() != BASS::STOPPED)
            return;
    }
    catch (const BASS::Exception& ex)
    {
        throw QException(QString("BASS Exception: ") + ex.what());
    }

    m_timer->stop();
    m_playState = STOPPED;
    emit SoundFinished();
}

void A_SoundImport::SetChannelVolume()
{
    float floatVol = m_volume / (float)VOLUME_MAX;
    try
    {
        m_channel->SetAttribute(BASS_ATTRIB_VOL, floatVol);
    }
    catch (const BASS::Exception& ex)
    {
        throw QException(QString("BASS Exception: ") + ex.what());
    }
}

void A_SoundImport::SetChannelPause(bool restart)
{
    try
    {
        if (m_paused && m_playState == PLAYING)
        {
            m_channel->Pause();
            m_playState = PAUSED;
        }
        else if (!m_paused && m_playState == PAUSED)
        {
            m_channel->Play(restart);
            m_playState = PLAYING;
        }
    }
    catch (const BASS::Exception& ex)
    {
        throw QException(QString("BASS Exception: ") + ex.what());
    }
}
