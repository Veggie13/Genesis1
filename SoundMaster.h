#ifndef SOUNDMASTER_H
#define SOUNDMASTER_H

#include <QMultiMap>

class Background;
namespace BASS { class Channel; }
namespace BASS { class Sample; }
class InstantSound;
class QByteArray;
template <typename T1, typename T2, typename T3> class QTriple;
class Song;


class SoundMaster
{
public:
    static SoundMaster& Get();
    static void Shutdown();

    bool ImportStream(const QString& filename, const QString& title);
    bool ImportSample(const QString& filename, const QString& title);

    void CloseStream(const QString& title);
    void CloseSample(const QString& title);

    Song*           CreateSong(const QString& title);
    Background*     CreateBackground(const QString& title);
    InstantSound*   CreateInstant(const QString& title);

    void ReturnSong(Song* song);
    void ReturnBackground(Background* bg);
    void ReturnInstant(InstantSound* inst);

private:
    SoundMaster();
    ~SoundMaster();

    BASS::Channel* GetStreamInstance(const QString& title);
    BASS::Channel* GetSampleInstance(const QString& title);


    typedef QMap<QString, BASS::Channel*> StreamMap;
    typedef QMap<QString, QTriple<BASS::Sample*, QByteArray, BASS::Channel*> > SampleMap;
    typedef QMultiMap<QString, Song*> SongMap;
    typedef QMultiMap<QString, Background*> BackgroundMap;
    typedef QMultiMap<QString, InstantSound*> InstantMap;

    StreamMap m_streamMap;
    SampleMap m_sampleMap;

    SongMap         m_songMap;
    BackgroundMap   m_bgMap;
    InstantMap      m_instMap;


    static SoundMaster* singleton;

};

#endif
