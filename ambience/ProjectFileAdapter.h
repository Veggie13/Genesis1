#ifndef PROJECTFILEADAPTER_H
#define PROJECTFILEADAPTER_H

#include "Soundboard.qoh"


class A_ImportManager;
class A_SoundImport;
class A_SoundInstance;
class MasterCtrl;
class MusicCtrl;
class Project;
class QDomDocument;
class QDomElement;
class QFile;
class RandomSound;
class Scene;
class State;

class ProjectFileAdapter
{
public:
    Project* CreateProjectFromFile(QFile& loadFile);
    void SaveProjectToFile(Project* project, QFile& file);

private:
    Project* LoadFromElement(const QString& filename, const QDomElement& root);
    void LoadStreamImportList(
        Project* parent,
        const QDomElement& longImports );
    void LoadSampleImportList(
        Project* parent,
        const QDomElement& shortImports );
    void LoadProjectBody(Project* proj, const QDomElement& project);
    void LoadScene(
        Project* proj,
        Scene* newScene,
        const QDomElement& scene );
    void LoadState(
        Project* proj,
        State* newState,
        const QDomElement& state );
    void LoadMusicData(
        Project* proj,
        State* parent,
        const QDomElement& musicData );
    void LoadBackgroundData(
        Project* proj,
        State* parent,
        const QDomElement& bgData );
    void LoadRandomData(
        Project* proj,
        State* parent,
        const QDomElement& randData );
    void LoadSoundboardData(
        Project* proj,
        State* parent,
        const QDomElement& sndboardData );

    void SaveToElement(QDomDocument& doc, Project* proj);
    void SaveStreamImportList(QDomElement& parent, A_ImportManager* mgr);
    void SaveSampleImportList(QDomElement& parent, A_ImportManager* mgr);
    void SaveImport(QDomElement& parent, A_SoundImport* import);
    void SaveImportList(QDomElement& element, A_ImportManager* mgr);
    void SaveProjectBody(QDomElement& parent, Project* proj);
    void SaveScene(QDomElement& parent, Scene* scene);
    void SaveState(QDomElement& parent, State* state);
    void SaveMusicData(QDomElement& parent, MusicCtrl* musicCtrl);
    void SaveBackgroundData(QDomElement& parent, MasterCtrl* bgCtrl);
    void SaveRandomData(QDomElement& parent, MasterCtrl* randCtrl);
    void SaveSoundboardData(QDomElement& parent, Soundboard* sndboard);
    void SaveSong(QDomElement& parent, A_SoundInstance* instance);
    void SaveBackground(QDomElement& parent, A_SoundInstance* instance);
    void SaveRandomSound(QDomElement& parent, RandomSound* instance);
    void SaveSoundboardEffect(
        QDomElement& parent,
        Soundboard::SoundGrid::const_iterator soundGridIt );


    static const char DOC_TYPE[];
    static const char ROOT_NAME[];
    static const char LONG_IMPORT_TAG[];
    static const char SHORT_IMPORT_TAG[];
    static const char PROJECT_TAG[];
    static const char FILE_TAG[];
    static const char SCENE_TAG[];
    static const char STATE_TAG[];
    static const char MUSIC_TAG[];
    static const char BACKGROUND_TAG[];
    static const char RANDOM_TAG[];
    static const char SOUNDBOARD_TAG[];
    static const char SONG_TAG[];
    static const char BACKGROUND_INSTANCE_TAG[];
    static const char RANDOM_INSTANCE_TAG[];
    static const char SOUNDBOARD_INSTANCE_TAG[];

    static const char COPY_LOCAL_ATTR[];
    static const char TITLE_ATTR[];
    static const char PATH_ATTR[];
    static const char VOLUME_ATTR[];
    static const char PAUSE_ATTR[];
    static const char PERIOD_ATTR[];
    static const char PERIOD_TYPE_ATTR[];
    static const char VARIANCE_ATTR[];
    static const char NUM_ROWS_ATTR[];
    static const char NUM_COLS_ATTR[];
    static const char ROW_ATTR[];
    static const char COL_ATTR[];
    static const char VERSION_ATTR[];

};

#endif
