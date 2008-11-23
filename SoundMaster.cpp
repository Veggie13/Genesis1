#include <QByteArray>
#include <QFile>
#include <QList>
#include <QMap>

#include <bass_system.h>
#include <bass_sample.h>
#include <bass_stream.h>

#include "Background.h"
#include "InstantSound.h"
#include "QTriple.hpp"
#include "Song.h"

#include "SoundMaster.h"


SoundMaster* SoundMaster::singleton = NULL;

SoundMaster::SoundMaster()
{
    BASS::System::Get().Init(-1,44100,0,0,NULL);
}

SoundMaster::~SoundMaster()
{
    for ( SongMap::iterator songIt = m_songMap.begin();
          songIt != m_songMap.end();
          songIt++ )
    {
        delete songIt.value();
    }

    for ( BackgroundMap::iterator bgIt = m_bgMap.begin();
          bgIt != m_bgMap.end();
          bgIt++ )
    {
        delete bgIt.value();
    }

    for ( InstantMap::iterator instIt = m_instMap.begin();
          instIt != m_instMap.end();
          instIt++ )
    {
        delete instIt.value();
    }

    for ( StreamMap::iterator streamIt = m_streamMap.begin();
          streamIt != m_streamMap.end();
          streamIt++ )
    {
        delete streamIt.value();
    }

    for ( SampleMap::iterator sampleIt = m_sampleMap.begin();
          sampleIt != m_sampleMap.end();
          sampleIt++ )
    {
        delete sampleIt.value().third;
        delete sampleIt.value().first;
    }

    BASS::System::Free();
}

SoundMaster& SoundMaster::Get()
{
    if (!singleton)
        singleton = new SoundMaster;

    return *singleton;
}

void SoundMaster::Shutdown()
{
    if (singleton)
    {
        delete singleton;
        singleton = NULL;
    }
}

bool SoundMaster::ImportStream(const QString& filename, const QString& title)
{
    if (m_streamMap.find(title) != m_streamMap.end())
        return false;


    BASS::Stream* newStream;
    try
    {
        newStream =
            BASS::System::Get().LoadStreamFromFile(filename.toAscii().data(),0,0,0);
    }
    catch (std::exception e)
    {
        fprintf(stderr, "BASS Exception: %s\n", e.what());
        return false;
    }

    m_streamMap[title] = newStream;
    return true;
}

bool SoundMaster::ImportSample(const QString& filename, const QString& title)
{
    if (m_sampleMap.find(title) != m_sampleMap.end())
        return false;

    QFile sampleFile(filename);
    if (!sampleFile.open(QIODevice::ReadOnly))
        return false;

    SampleMap::mapped_type& newEntry = m_sampleMap[title];
    newEntry.second = sampleFile.readAll();
    sampleFile.close();

    BASS::Sample* newSample;
    try
    {
        newSample =
            BASS::System::Get().LoadSampleFromMemory(
                newEntry.second.data(),
                newEntry.second.length(),
                2,
                BASS_SAMPLE_OVER_POS );

        newEntry.first = newSample;
        newEntry.third = newSample->GetChannel(false);
    }
    catch (std::exception e)
    {
        fprintf(stderr, "BASS System Exception: %s\n", e.what());
        return false;
    }

    return true;
}

void SoundMaster::CloseStream(const QString& title)
{
    StreamMap::iterator doomed = m_streamMap.find(title);
    if (doomed == m_streamMap.end())
        return;

    SongMap::iterator songIt = m_songMap.find(title);
    while ( (songIt != m_songMap.end()) &&
            (songIt.key() == title) )
    {
        delete songIt.value();
        m_songMap.erase(songIt);
    }

    BackgroundMap::iterator bgIt = m_bgMap.find(title);
    while ( (bgIt != m_bgMap.end()) &&
            (bgIt.key() == title) )
    {
        delete bgIt.value();
        m_bgMap.erase(bgIt);
    }

    delete doomed.value();
    m_streamMap.erase(doomed);
}

void SoundMaster::CloseSample(const QString& title)
{
    SampleMap::iterator doomed = m_sampleMap.find(title);
    if (doomed == m_sampleMap.end())
        return;

    InstantMap::iterator instIt = m_instMap.find(title);
    while ( (instIt != m_instMap.end()) &&
            (instIt.key() == title) )
    {
        delete instIt.value();
        m_instMap.erase(instIt);
    }

    delete doomed.value().third;
    delete doomed.value().first;
    m_sampleMap.erase(doomed);
}

BASS::Channel* SoundMaster::GetStreamInstance(const QString& title)
{
    StreamMap::iterator it = m_streamMap.find(title);
    if (it == m_streamMap.end())
        return NULL;

    return it.value();
}

BASS::Channel* SoundMaster::GetSampleInstance(const QString& title)
{
    SampleMap::iterator it = m_sampleMap.find(title);
    if (it == m_sampleMap.end())
        return NULL;

    return it.value().third;
}

Song* SoundMaster::CreateSong(const QString& title)
{
    Song* ret = new Song( GetStreamInstance(title) );
    m_songMap.insert(title, ret);

    return ret;
}

Background* SoundMaster::CreateBackground(const QString& title)
{
    Background* ret = new Background( GetStreamInstance(title) );
    m_bgMap.insert(title, ret);

    return ret;
}

InstantSound* SoundMaster::CreateInstant(const QString& title)
{
    InstantSound* ret = new InstantSound( GetSampleInstance(title) );
    m_instMap.insert(title, ret);

    return ret;
}

void SoundMaster::ReturnSong(Song* song)
{
    for ( QMap<QString, Song*>::iterator it = m_songMap.begin();
          it != m_songMap.end();
          it++ )
    {
        if (it.value() == song)
        {
            delete song;
            m_songMap.erase(it);
            return;
        }
    }
}

void SoundMaster::ReturnBackground(Background* bg)
{
    for ( QMap<QString, Background*>::iterator it = m_bgMap.begin();
          it != m_bgMap.end();
          it++ )
    {
        if (it.value() == bg)
        {
            delete bg;
            m_bgMap.erase(it);
            return;
        }
    }
}

void SoundMaster::ReturnInstant(InstantSound* inst)
{
    for ( QMap<QString, InstantSound*>::iterator it = m_instMap.begin();
          it != m_instMap.end();
          it++ )
    {
        if (it.value() == inst)
        {
            delete inst;
            m_instMap.erase(it);
            return;
        }
    }
}
