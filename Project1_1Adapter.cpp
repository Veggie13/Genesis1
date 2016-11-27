#include "Project1_1Adapter.h"


const AmbienceVersion Project1_1Adapter::VERSION_1_1("1.1 rev 00 alpha");

Project* Project1_1Adapter::LoadFromElement(
    const AmbienceVersion& fileVersion,
    const QDomElement& root )
{
    if (fileVersion < VERSION_1_1)
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

void Project1_1Adapter::LoadStreamImportList(
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

void Project1_1Adapter::LoadSampleImportList(
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

void Project1_1Adapter::LoadProjectBody(Project* proj, const QDomElement& project)
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

void Project1_1Adapter::LoadScene(
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

void Project1_1Adapter::LoadState(
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

void Project1_1Adapter::LoadMusicData(
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

void Project1_1Adapter::LoadBackgroundData(
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

void Project1_1Adapter::LoadRandomData(
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

void Project1_1Adapter::LoadSoundboardData(
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
