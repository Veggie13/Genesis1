#include <QByteArray>
#include <QFile>
#include <QList>
#include <QMap>

#include <bass_system.h>
#include <bass_sample.h>
#include <bass_stream.h>

#include "Background.qoh"
#include "InstantSound.qoh"
#include "QTriple.hpp"
#include "Song.qoh"

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
        delete sampleIt.value().second;
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


    QByteArray* newArray = NULL; // avoid annoying warning
    newArray = new QByteArray( sampleFile.readAll() );
    sampleFile.close();

    BASS::Sample* newSample;
    try
    {
        newSample =
            BASS::System::Get().LoadSampleFromMemory(
                newArray->data(),
                newArray->length(),
                2,
                BASS_SAMPLE_OVER_POS );
    }
    catch (std::exception e)
    {
        fprintf(stderr, "BASS System Exception: %s\n", e.what());
        delete newArray;
        return false;
    }

    SampleMap::mapped_type& newEntry = m_sampleMap[title];
    newEntry.first = newSample;
    newEntry.second = newArray;
    newEntry.third = newSample->GetChannel(false);

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
    delete doomed.value().second;
    m_sampleMap.erase(doomed);
}

bool SoundMaster::RenameStream(const QString& title, const QString& newTitle)
{
    StreamMap::iterator oldStream = m_streamMap.find(title);
    if (oldStream == m_streamMap.end())
        return false;

    if (title == newTitle)
        return false;

    StreamMap::iterator newChecker = m_streamMap.find(newTitle);
    if (newChecker != m_streamMap.end())
        return false;

    SongMap::iterator songIt = m_songMap.find(title);
    while ( (songIt != m_songMap.end()) &&
            (songIt.key() == title) )
    {
        m_songMap.insert(newTitle, songIt.value());
        m_songMap.erase(songIt);
    }

    BackgroundMap::iterator bgIt = m_bgMap.find(title);
    while ( (bgIt != m_bgMap.end()) &&
            (bgIt.key() == title) )
    {
        m_bgMap.insert(newTitle, bgIt.value());
        m_bgMap.erase(bgIt);
    }

    m_streamMap[newTitle] = oldStream.value();
    m_streamMap.erase(oldStream);

    return true;
}

bool SoundMaster::RenameSample(const QString& title, const QString& newTitle)
{
    SampleMap::iterator oldSample = m_sampleMap.find(title);
    if (oldSample == m_sampleMap.end())
        return false;

    if (title == newTitle)
        return false;

    SampleMap::iterator newChecker = m_sampleMap.find(newTitle);
    if (newChecker != m_sampleMap.end())
        return false;

    InstantMap::iterator instIt = m_instMap.find(title);
    while ( (instIt != m_instMap.end()) &&
            (instIt.key() == title) )
    {
        m_instMap.insert(newTitle, instIt.value());
        m_instMap.erase(instIt);
    }

    m_sampleMap[newTitle] = oldSample.value();
    m_sampleMap.erase(oldSample);

    return true;
}

bool SoundMaster::ReimportStream(const QString& title, const QString& newFilename)
{
    if (m_streamMap.find(title) == m_streamMap.end())
        return false;


    BASS::Stream* newStream;
    try
    {
        newStream =
            BASS::System::Get().LoadStreamFromFile(newFilename.toAscii().data(),0,0,0);
    }
    catch (std::exception e)
    {
        fprintf(stderr, "BASS Exception: %s\n", e.what());
        return false;
    }

    SongMap::iterator songIt = m_songMap.find(title);
    while ( (songIt != m_songMap.end()) &&
            (songIt.key() == title) )
    {
        Song* changer = songIt.value();
        bool cond = changer->IsActive();

        if (cond)
            changer->StopNoSignal();
        changer->Reassign(newStream);
        if (cond)
            changer->Play();

        songIt++;
    }

    BackgroundMap::iterator bgIt = m_bgMap.find(title);
    while ( (bgIt != m_bgMap.end()) &&
            (bgIt.key() == title) )
    {
        Background* changer = bgIt.value();
        bool cond = changer->IsActive();

        if (cond)
            changer->Stop();
        changer->Reassign(newStream);
        if (cond)
            changer->Play();

        bgIt++;
    }

    delete m_streamMap[title];
    m_streamMap[title] = newStream;

    return true;
}

bool SoundMaster::ReimportSample(const QString& title, const QString& newFilename)
{
    if (m_sampleMap.find(title) == m_sampleMap.end())
        return false;

    QFile sampleFile(newFilename);
    if (!sampleFile.open(QIODevice::ReadOnly))
        return false;


    QByteArray* newArray = NULL; // avoid annoying warning
    newArray = new QByteArray( sampleFile.readAll() );
    sampleFile.close();

    BASS::Sample* newSample;
    try
    {
        newSample =
            BASS::System::Get().LoadSampleFromMemory(
                newArray->data(),
                newArray->length(),
                2,
                BASS_SAMPLE_OVER_POS );
    }
    catch (std::exception e)
    {
        fprintf(stderr, "BASS System Exception: %s\n", e.what());
        delete newArray;
        return false;
    }

    SampleMap::mapped_type& entry = m_sampleMap[title];
    SampleMap::mapped_type newEntry = entry;
    newEntry.first = newSample;
    newEntry.second = newArray;
    newEntry.third = newSample->GetChannel(false);

    InstantMap::iterator instIt = m_instMap.find(title);
    while ( (instIt != m_instMap.end()) &&
            (instIt.key() == title) )
    {
        instIt.value()->Reassign(newEntry.third);
        instIt++;
    }

    delete entry.third;
    delete entry.first;
    delete entry.second;

    entry = newEntry;

    return true;
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
