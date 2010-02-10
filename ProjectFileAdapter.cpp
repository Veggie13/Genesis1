#include <stdexcept>

#include <QDir>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>

#include "A_ImportManager.qoh"
#include "A_SoundImport.qoh"
#include "A_SoundInstance.qoh"
#include "AmbienceVersion.h"
#include "Background.h"
#include "MasterCtrl.qoh"
#include "MusicCtrl.qoh"
#include "Project.qoh"
#include "RandomSound.qoh"
#include "Scene.qoh"
#include "SoundboardInstance.h"
#include "StartableSound.qoh"
#include "State.qoh"

#include "ProjectFileAdapter.h"


const char ProjectFileAdapter::DOC_TYPE[] = "assp";
const char ProjectFileAdapter::ROOT_NAME[] = "ambience";
const char ProjectFileAdapter::LONG_IMPORT_TAG[] = "limports";
const char ProjectFileAdapter::SHORT_IMPORT_TAG[] = "simports";
const char ProjectFileAdapter::PROJECT_TAG[] = "project";
const char ProjectFileAdapter::FILE_TAG[] = "file";
const char ProjectFileAdapter::SCENE_TAG[] = "scene";
const char ProjectFileAdapter::STATE_TAG[] = "state";
const char ProjectFileAdapter::MUSIC_TAG[] = "music";
const char ProjectFileAdapter::BACKGROUND_TAG[] = "background";
const char ProjectFileAdapter::RANDOM_TAG[] = "random";
const char ProjectFileAdapter::SOUNDBOARD_TAG[] = "soundboard";
const char ProjectFileAdapter::SONG_TAG[] = "song";
const char ProjectFileAdapter::BACKGROUND_INSTANCE_TAG[] = "sound";
const char ProjectFileAdapter::RANDOM_INSTANCE_TAG[] = "effect";
const char ProjectFileAdapter::SOUNDBOARD_INSTANCE_TAG[] = "effect";

const char ProjectFileAdapter::COPY_LOCAL_ATTR[] = "copyLocal";
const char ProjectFileAdapter::TITLE_ATTR[] = "title";
const char ProjectFileAdapter::PATH_ATTR[] = "path";
const char ProjectFileAdapter::VOLUME_ATTR[] = "vol";
const char ProjectFileAdapter::PAUSE_ATTR[] = "mute";
const char ProjectFileAdapter::PERIOD_ATTR[] = "per";
const char ProjectFileAdapter::PERIOD_TYPE_ATTR[] = "perType";
const char ProjectFileAdapter::VARIANCE_ATTR[] = "var";
const char ProjectFileAdapter::NUM_ROWS_ATTR[] = "rows";
const char ProjectFileAdapter::NUM_COLS_ATTR[] = "cols";
const char ProjectFileAdapter::ROW_ATTR[] = "row";
const char ProjectFileAdapter::COL_ATTR[] = "col";
const char ProjectFileAdapter::VERSION_ATTR[] = "ver";

Project* ProjectFileAdapter::CreateProjectFromFile(QFile& loadFile)
{
    QDomDocument doc(DOC_TYPE);
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Could not read from the chosen file.");
    }
    if (!doc.setContent(&loadFile))
    {
        loadFile.close();
        throw std::runtime_error("Could not read from the chosen file.");
    }
    loadFile.close();

    return LoadFromElement(loadFile.fileName(), doc.documentElement());
}

void ProjectFileAdapter::SaveProjectToFile(
    Project* project,
    QFile& file )
{
    if (!file.open(QIODevice::WriteOnly))
    {
        throw std::runtime_error("Could not write to the chosen file.");
    }

    QDomDocument doc(DOC_TYPE);
    SaveToElement(doc, project);
    file.write(doc.toString().toAscii());
    file.close();
}

Project* ProjectFileAdapter::LoadFromElement(const QString& filename, const QDomElement& root)
{
    if (root.tagName() != ROOT_NAME)
        throw std::runtime_error("Not an Ambience file.");

    AmbienceVersion fileVersion(root.attribute(VERSION_ATTR, ""));
    if (!fileVersion.IsValid() || fileVersion > AmbienceVersion::CURRENT_VERSION)
        throw std::runtime_error("Unsupported file version.");

    QDomElement longImports;
    QDomElement shortImports;
    QDomElement project;
    for( QDomNode n = root.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement child = n.toElement();
        if ( child.isNull() )
            continue;

        if (child.tagName() == LONG_IMPORT_TAG && longImports.isNull())
            longImports = child;
        else if (child.tagName() == SHORT_IMPORT_TAG && shortImports.isNull())
            shortImports = child;
        else if (child.tagName() == PROJECT_TAG && project.isNull())
            project = child;
    }

    QString errorMsg = "";
    if (longImports.isNull())
        errorMsg += "- Missing stream imports.\n";
    if (shortImports.isNull())
        errorMsg += "- Missing sample imports.\n";
    if (project.isNull())
        errorMsg += "- Missing project body.\n";

    if (errorMsg != "")
    {
        errorMsg = QString("Improperly formatted file:\n\n") + errorMsg;
        throw std::runtime_error(errorMsg.toStdString());
    }

    Project* newProj = new Project;

    QFileInfo info(filename);
    newProj->StreamManager()->SetProjectPath(info.dir().absolutePath());
    newProj->SampleManager()->SetProjectPath(info.dir().absolutePath());

    LoadStreamImportList(newProj, longImports);
    LoadSampleImportList(newProj, shortImports);
    LoadProjectBody(newProj, project);

    return newProj;
}

void ProjectFileAdapter::LoadStreamImportList(
    Project* parent,
    const QDomElement& longImports )
{
    bool copyLocal = longImports.attribute(COPY_LOCAL_ATTR, "0").toInt();
    parent->StreamManager()->SetCopyLocal(copyLocal);

    for( QDomNode n = longImports.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement file = n.toElement();
        if ( file.isNull() || file.tagName() != FILE_TAG )
            continue;

        QString fileTitle = file.attribute(TITLE_ATTR, "");
        QString filePath = file.attribute(PATH_ATTR, "");

        parent->StreamManager()->ImportFile(fileTitle, filePath);
    }
}

void ProjectFileAdapter::LoadSampleImportList(
    Project* parent,
    const QDomElement& shortImports )
{
    bool copyLocal = shortImports.attribute(COPY_LOCAL_ATTR, "0").toInt();
    parent->SampleManager()->SetCopyLocal(copyLocal);

    for( QDomNode n = shortImports.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement file = n.toElement();
        if ( file.isNull() || file.tagName() != FILE_TAG )
            continue;

        QString fileTitle = file.attribute(TITLE_ATTR, "");
        QString filePath = file.attribute(PATH_ATTR, "");

        parent->SampleManager()->ImportFile(fileTitle, filePath);
    }
}

void ProjectFileAdapter::LoadProjectBody(Project* proj, const QDomElement& project)
{
    for( QDomNode n = project.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement scene = n.toElement();
        if ( scene.isNull() || scene.tagName() != SCENE_TAG )
            throw std::runtime_error("Improperly formatted Project body.");

        QString sceneTitle = scene.attribute(TITLE_ATTR, "");

        Scene* newScene = new Scene(sceneTitle, proj);
        proj->AddScene(newScene);
        LoadScene(proj, newScene, scene);
    }
}

void ProjectFileAdapter::LoadScene(
    Project* proj,
    Scene* newScene,
    const QDomElement& scene )
{
    for( QDomNode n = scene.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement state = n.toElement();
        if ( state.isNull() || state.tagName() != STATE_TAG )
            throw std::runtime_error("Improperly formatted Scene data");

        QString stateTitle = state.attribute(TITLE_ATTR, "");
        State* newState = new State(stateTitle, newScene);
        newScene->AddState(newState);
        LoadState(proj, newState, state);
    }
}

void ProjectFileAdapter::LoadState(
    Project* proj,
    State* newState,
    const QDomElement& state )
{
    QDomElement musicData;
    QDomElement bgData;
    QDomElement randData;
    QDomElement sndboardData;
    for( QDomNode n = state.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement child = n.toElement();
        if ( child.isNull() )
            throw std::runtime_error("Improperly formatted State data.");

        if (child.tagName() == MUSIC_TAG)
        {
            if (!musicData.isNull())
                throw std::runtime_error("Cannot have multiple Music data sections.");
            musicData = child;
        }
        else if (child.tagName() == BACKGROUND_TAG)
        {
            if (!bgData.isNull())
                throw
                    std::runtime_error("Cannot have multiple Background data sections.");
            bgData = child;
        }
        else if (child.tagName() == RANDOM_TAG)
        {
            if (!randData.isNull())
                throw std::runtime_error("Cannot have multiple Random data sections.");
            randData = child;
        }
        else if (child.tagName() == SOUNDBOARD_TAG)
        {
            if (!sndboardData.isNull())
                throw std::runtime_error("Cannot have multiple Soundboard data sections.");
            sndboardData = child;
        }
    }

    QString errorMsg = "";
    if (musicData.isNull())
        errorMsg += "- Missing Music data section.\n";
    if (bgData.isNull())
        errorMsg += "- Missing Background data section.\n";
    if (randData.isNull())
        errorMsg += "- Missing Random data section.\n";
    if (sndboardData.isNull())
        errorMsg += "- Missing Soundboard data section.\n";

    if (errorMsg != "")
    {
        errorMsg = QString("Improperly formatted file:\n\n") + errorMsg;
        throw std::runtime_error(errorMsg.toStdString());
    }

    LoadMusicData(proj, newState, musicData);
    LoadBackgroundData(proj, newState, bgData);
    LoadRandomData(proj, newState, randData);
    LoadSoundboardData(proj, newState, sndboardData);
}

void ProjectFileAdapter::LoadMusicData(
    Project* proj,
    State* parent,
    const QDomElement& musicData )
{
    MusicCtrl* ctrl = parent->GetMusicController();

    QString vol = musicData.attribute(VOLUME_ATTR, "0");
    QString mute = musicData.attribute(PAUSE_ATTR, "0");

    ctrl->SetVolume(vol.toInt());
    ctrl->SetPaused(mute.toInt());
    for( QDomNode n = musicData.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement song = n.toElement();
        if ( song.isNull() || song.tagName() != SONG_TAG )
            throw std::runtime_error("Improperly formatted Music section.");

        QString songTitle = song.attribute(TITLE_ATTR, "");
        StartableSound* newSong = new StartableSound(
            proj->StreamManager()->GetImport(songTitle)
            );
        ctrl->AddInstance(newSong);
    }
}

void ProjectFileAdapter::LoadBackgroundData(
    Project* proj,
    State* parent,
    const QDomElement& bgData )
{
    MasterCtrl* ctrl = parent->GetBackgroundController();

    QString vol = bgData.attribute(VOLUME_ATTR, "0");
    QString mute = bgData.attribute(PAUSE_ATTR, "0");

    ctrl->SetVolume(vol.toInt());
    ctrl->SetPaused(mute.toInt());
    for( QDomNode n = bgData.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement sound = n.toElement();
        if ( sound.isNull() || sound.tagName() != BACKGROUND_INSTANCE_TAG )
            throw std::runtime_error("Improperly formatted Background section.");

        QString soundTitle = sound.attribute(TITLE_ATTR, "");
        Background* newBg = new Background(
            proj->StreamManager()->GetImport(soundTitle)
            );
        ctrl->AddInstance(newBg);

        QString soundVol = sound.attribute(VOLUME_ATTR, "0");
        QString soundMute = sound.attribute(PAUSE_ATTR, "0");

        newBg->SetInstanceVolume(soundVol.toInt());
        newBg->SetInstancePaused(soundMute.toInt());
    }
}

void ProjectFileAdapter::LoadRandomData(
    Project* proj,
    State* parent,
    const QDomElement& randData )
{
    MasterCtrl* ctrl = parent->GetRandomController();

    QString vol = randData.attribute(VOLUME_ATTR, "0");
    QString mute = randData.attribute(PAUSE_ATTR, "0");

    ctrl->SetVolume(vol.toInt());
    ctrl->SetPaused(mute.toInt());
    for( QDomNode n = randData.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement effect = n.toElement();
        if ( effect.isNull() || effect.tagName() != RANDOM_INSTANCE_TAG )
            throw std::runtime_error("Improperly formatted Random section.");

        QString effectTitle = effect.attribute(TITLE_ATTR, "");
        RandomSound* newRand = new RandomSound(
            proj->SampleManager()->GetImport(effectTitle)
            );
        ctrl->AddInstance(newRand);

        QString effectVol = effect.attribute(VOLUME_ATTR, "0");
        QString effectPer = effect.attribute(PERIOD_ATTR, "0");
        QString effectPerType = effect.attribute(PERIOD_TYPE_ATTR, "1");
        QString effectVar = effect.attribute(VARIANCE_ATTR, "0");
        QString effectMute = effect.attribute(PAUSE_ATTR, "0");

        newRand->SetInstanceVolume(effectVol.toInt());
        newRand->SetPeriod(effectPer.toDouble());
        newRand->SetPeriodType(
            RandomSound::PeriodTypes[ effectPerType.toInt() ]
            );
        newRand->SetVariance(effectVar.toInt());
        newRand->SetInstancePaused(effectMute.toInt());
    }
}

void ProjectFileAdapter::LoadSoundboardData(
    Project* proj,
    State* parent,
    const QDomElement& sndboardData )
{
    Soundboard* sndboard = parent->GetSoundboard();

    QString vol = sndboardData.attribute(VOLUME_ATTR, "0");
    QString rows = sndboardData.attribute(NUM_ROWS_ATTR, "1");
    QString cols = sndboardData.attribute(NUM_COLS_ATTR, "1");

    sndboard->SetVolume(vol.toInt());
    sndboard->Resize(rows.toInt(), cols.toInt());
    for( QDomNode n = sndboardData.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement effect = n.toElement();
        if ( effect.isNull() || effect.tagName() != SOUNDBOARD_INSTANCE_TAG )
            continue;

        QString effectTitle = effect.attribute(TITLE_ATTR, "");
        QString effectRow = effect.attribute(ROW_ATTR, "-1");
        QString effectCol = effect.attribute(COL_ATTR, "-1");

        SoundboardInstance* instance = new SoundboardInstance(
            proj->SampleManager()->GetImport(effectTitle)
            );
        sndboard->AddEntry(effectRow.toInt(), effectCol.toInt(), instance);
    }
}

void ProjectFileAdapter::SaveToElement(
    QDomDocument& doc,
    Project* proj )
{
    QDomElement root = doc.createElement(ROOT_NAME);
    root.setAttribute(VERSION_ATTR, AmbienceVersion::CURRENT_VERSION.GetVersionString());

    SaveStreamImportList(root, proj->StreamManager());
    SaveSampleImportList(root, proj->SampleManager());
    SaveProjectBody(root, proj);

    doc.appendChild(root);
}

void ProjectFileAdapter::SaveStreamImportList(QDomElement& parent, A_ImportManager* mgr)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement limports = doc.createElement(LONG_IMPORT_TAG);

    SaveImportList(limports, mgr);

    parent.appendChild(limports);
}

void ProjectFileAdapter::SaveSampleImportList(QDomElement& parent, A_ImportManager* mgr)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement simports = doc.createElement(SHORT_IMPORT_TAG);

    SaveImportList(simports, mgr);

    parent.appendChild(simports);
}

void ProjectFileAdapter::SaveImport(QDomElement& parent, A_SoundImport* import)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement file = doc.createElement(FILE_TAG);

    file.setAttribute(TITLE_ATTR, import->Title());
    file.setAttribute(PATH_ATTR, import->Filename());

    parent.appendChild(file);
}

void ProjectFileAdapter::SaveImportList(QDomElement& element, A_ImportManager* mgr)
{
    element.setAttribute(COPY_LOCAL_ATTR, (int)mgr->IsCopyLocalOn());

    const QList<A_SoundImport*>& importList = mgr->ImportList();
    for ( QList<A_SoundImport*>::const_iterator it = importList.begin();
          it != importList.end();
          it++ )
    {
        SaveImport(element, *it);
    }
}

void ProjectFileAdapter::SaveProjectBody(QDomElement& parent, Project* proj)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement project = doc.createElement(PROJECT_TAG);

    const QList<Scene*>& sceneList = proj->SceneList();
    for ( QList<Scene*>::const_iterator it = sceneList.begin();
          it != sceneList.end();
          it++ )
    {
        SaveScene(project, *it);
    }

    parent.appendChild(project);
}

void ProjectFileAdapter::SaveScene(QDomElement& parent, Scene* scene)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement sceneEl = doc.createElement(SCENE_TAG);

    sceneEl.setAttribute(TITLE_ATTR, scene->Title());

    const QList<State*>& stateList = scene->StateList();
    for ( QList<State*>::const_iterator it = stateList.begin();
          it != stateList.end();
          it++ )
    {
        SaveState(sceneEl, *it);
    }

    parent.appendChild(sceneEl);
}

void ProjectFileAdapter::SaveState(QDomElement& parent, State* state)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement stateEl = doc.createElement(STATE_TAG);

    stateEl.setAttribute(TITLE_ATTR, state->Title());

    SaveMusicData(stateEl, state->GetMusicController());
    SaveBackgroundData(stateEl, state->GetBackgroundController());
    SaveRandomData(stateEl, state->GetRandomController());
    SaveSoundboardData(stateEl, state->GetSoundboard());

    parent.appendChild(stateEl);
}

void ProjectFileAdapter::SaveMusicData(QDomElement& parent, MusicCtrl* musicCtrl)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement music = doc.createElement(MUSIC_TAG);

    music.setAttribute(VOLUME_ATTR, QString("%1").arg(musicCtrl->Volume()));
    music.setAttribute(PAUSE_ATTR, QString("%1").arg((int)musicCtrl->IsPaused()));

    const QList<A_SoundInstance*>& songList = musicCtrl->Children();
    for ( QList<A_SoundInstance*>::const_iterator it = songList.begin();
          it != songList.end();
          it++ )
    {
        SaveSong(music, *it);
    }

    parent.appendChild(music);
}

void ProjectFileAdapter::SaveBackgroundData(QDomElement& parent, MasterCtrl* bgCtrl)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement background = doc.createElement(BACKGROUND_TAG);

    background.setAttribute(VOLUME_ATTR, QString("%1").arg(bgCtrl->Volume()));
    background.setAttribute(PAUSE_ATTR, QString("%1").arg((int)bgCtrl->IsPaused()));

    const QList<A_SoundInstance*>& soundList = bgCtrl->Children();
    for ( QList<A_SoundInstance*>::const_iterator it = soundList.begin();
          it != soundList.end();
          it++ )
    {
        SaveBackground(background, *it);
    }

    parent.appendChild(background);
}

void ProjectFileAdapter::SaveRandomData(QDomElement& parent, MasterCtrl* randCtrl)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement random = doc.createElement(RANDOM_TAG);

    random.setAttribute(VOLUME_ATTR, QString("%1").arg(randCtrl->Volume()));
    random.setAttribute(PAUSE_ATTR, QString("%1").arg((int)randCtrl->IsPaused()));

    const QList<A_SoundInstance*>& effectList = randCtrl->Children();
    for ( QList<A_SoundInstance*>::const_iterator it = effectList.begin();
          it != effectList.end();
          it++ )
    {
        SaveRandomSound(random, dynamic_cast<RandomSound*>(*it));
    }

    parent.appendChild(random);
}

void ProjectFileAdapter::SaveSoundboardData(QDomElement& parent, Soundboard* sndboard)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement soundboard = doc.createElement(SOUNDBOARD_TAG);

    soundboard.setAttribute(VOLUME_ATTR, QString("%1").arg(sndboard->Volume()));
    soundboard.setAttribute(NUM_ROWS_ATTR, QString("%1").arg(sndboard->RowCount()));
    soundboard.setAttribute(NUM_COLS_ATTR, QString("%1").arg(sndboard->ColCount()));

    const Soundboard::SoundGrid& soundGrid = sndboard->GetSoundGrid();
    for ( Soundboard::SoundGrid::const_iterator it = soundGrid.begin();
          it != soundGrid.end();
          it++ )
    {
        SaveSong(soundboard, it.value());
    }

    parent.appendChild(soundboard);
}

void ProjectFileAdapter::SaveSong(QDomElement& parent, A_SoundInstance* instance)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement song = doc.createElement(SONG_TAG);

    song.setAttribute(TITLE_ATTR, instance->Title());

    parent.appendChild(song);
}

void ProjectFileAdapter::SaveBackground(QDomElement& parent, A_SoundInstance* instance)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement sound = doc.createElement(BACKGROUND_INSTANCE_TAG);

    sound.setAttribute(TITLE_ATTR, instance->Title());
    sound.setAttribute(
        VOLUME_ATTR,
        QString("%1")
            .arg( instance->InstanceVolume() ) );
    sound.setAttribute(
        PAUSE_ATTR,
        QString("%1")
            .arg( (int)instance->IsInstancePaused() ) );

    parent.appendChild(sound);
}

void ProjectFileAdapter::SaveRandomSound(QDomElement& parent, RandomSound* instance)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement effect = doc.createElement(RANDOM_INSTANCE_TAG);

    effect.setAttribute(TITLE_ATTR, instance->Title());
    effect.setAttribute(
        VOLUME_ATTR,
        QString("%1")
            .arg( instance->InstanceVolume() ) );
    effect.setAttribute(
        PERIOD_ATTR,
        QString("%1")
            .arg( instance->Period() ) );
    effect.setAttribute(
        PERIOD_TYPE_ATTR,
        QString("%1")
            .arg( (int)instance->GetPeriodType() ) );
    effect.setAttribute(
        VARIANCE_ATTR,
        QString("%1")
            .arg( instance->Variance() ) );
    effect.setAttribute(
        PAUSE_ATTR,
        QString("%1")
            .arg( (int)instance->IsInstancePaused() ) );

    parent.appendChild(effect);
}

void ProjectFileAdapter::SaveSoundboardEffect(
    QDomElement& parent,
    Soundboard::SoundGrid::const_iterator soundGridIt )
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement effect = doc.createElement(SOUNDBOARD_INSTANCE_TAG);

    effect.setAttribute(ROW_ATTR, QString("%1").arg(soundGridIt.key().first));
    effect.setAttribute(COL_ATTR, QString("%1").arg(soundGridIt.key().second));
    effect.setAttribute(TITLE_ATTR, soundGridIt.value()->Title());

    parent.appendChild(effect);
}

