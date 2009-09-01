#include <QCloseEvent>
#include <QDomElement>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QMap>
#include <QMessageBox>
#include <QSettings>
#include <QShowEvent>
#include <QTimer>

#include "A_ImportManager.qoh"
#include "A_SoundImport.qoh"
#include "AboutDlgUi.h"
#include "Background.h"
#include "BackgroundCtrlPanel.qoh"
#include "FileSelectionDlg.qoh"
#include "MasterCtrl.qoh"
#include "MusicCtrl.qoh"
#include "MusicCtrlPanel.qoh"
#include "OpenOptionsDlg.qoh"
#include "Project.qoh"
#include "QException.h"
#include "RandomCtrlPanel.qoh"
#include "RandomSound.qoh"
#include "Scene.qoh"
#include "SceneEditorDlg.qoh"
#include "SceneState.qoh"
#include "Soundboard.qoh"
#include "SoundboardInstance.h"
#include "SoundboardLayout.qoh"
#include "StartableSound.qoh"
#include "State.qoh"

#include "AmbMainWindow.qoh"


const char          AmbMainWindow::VERSION_FORMAT[]         = "%1.%2 rev %3%4";
const unsigned int  AmbMainWindow::VERSION_CODE             = 0x01020001;
const char          AmbMainWindow::APP_NAME[]               = "Ambience Sound Studio";
const char          AmbMainWindow::COMPANY_NAME[]           = "MeiCor Gaming";
const int           AmbMainWindow::RECENT_FILES_LIST_MAX    = 8;

AmbMainWindow::AmbMainWindow(int argc, char* argv[], QWidget* parent)
:   PopupToolMainWindow(parent),
    m_sceneState(NULL),
    m_musicCtrl(NULL),
    m_bgCtrl(NULL),
    m_randCtrl(NULL),
    m_sndboardObj(NULL),
    m_project(NULL),
    m_projectPath(""),
    m_modified(false),
    m_curState(NULL),
    m_sceneEditDlg(NULL),
    m_longFileDlg(NULL),
    m_shortFileDlg(NULL),
    m_starting(true),
    m_settings(NULL),
    m_tempFrame(NULL)
{
    setupUi(this);
    setupPopupUi();

    // Create all control panels.
    m_sceneState = new SceneState;
    m_musicCtrl = new MusicCtrlPanel;
    m_bgCtrl = new BackgroundCtrlPanel;
    m_randCtrl = new RandomCtrlPanel;
    m_sndboardObj = new SoundboardLayout;

    // Add hover/popup widgets.
    addPopupWidget("Scene/State", m_sceneState);
    addPopupWidget("Music", m_musicCtrl);
    addPopupWidget("Background", m_bgCtrl);
    addPopupWidget("Random", m_randCtrl);

    // Setup soundboard.
    m_sndboardObj->setupUiWithButtons(mainAreaWidget());

    // Create all dialogs.
    m_sceneEditDlg = new SceneEditorDlg(this);
    m_longFileDlg = new FileSelectionDlg(this);
    m_shortFileDlg = new FileSelectionDlg(this);

    // Setup file dialogs.
    m_longFileDlg->setWindowTitle("Streamed file Import");
    m_shortFileDlg->setWindowTitle("Sampled file Import");

    // Connect signals.
    connect(m_newAction, SIGNAL( triggered() ), this, SLOT( NewProject() ));
    connect(m_openAction, SIGNAL( triggered() ), this, SLOT( Load() ));
    connect(m_saveAction, SIGNAL( triggered() ), this, SLOT( Save() ));
    connect(m_saveAsAction, SIGNAL( triggered() ), this, SLOT( SaveAs() ));
    connect(m_scenesAction, SIGNAL( triggered() ), m_sceneEditDlg, SLOT( exec() ));
    connect(m_longAction, SIGNAL( triggered() ), m_longFileDlg, SLOT( ExecNoSelection() ));
    connect(m_shortAction, SIGNAL( triggered() ), m_shortFileDlg, SLOT( ExecNoSelection() ));
    connect( m_copyLongAction,  SIGNAL( toggled(bool)      ),
             this,              SLOT  ( SetCopyLocal(bool) ) );
    connect( m_copyShortAction, SIGNAL( toggled(bool)      ),
             this,              SLOT  ( SetCopyLocal(bool) ) );
    connect(m_aboutAction, SIGNAL( triggered() ), this, SLOT( ShowAboutDlg() ));

    connect( m_sceneState,  SIGNAL( SceneStateSwitched(Scene*, State*) ),
             this,          SLOT  ( SwitchSceneState(Scene*, State*)   ) );

    connect( m_musicCtrl,   SIGNAL( AddSelected()           ),
             this,          SLOT  ( SelectSong()            ) );
    connect( m_bgCtrl,      SIGNAL( AddSelected()           ),
             this,          SLOT  ( SelectBackground()      ) );
    connect( m_randCtrl,    SIGNAL( AddSelected()           ),
             this,          SLOT  ( SelectRandom()          ) );
    connect( m_sndboardObj, SIGNAL( SoundRequested(int,int) ),
             this,          SLOT  ( SelectInstant(int,int)  ) );

    // Apply settings.
    m_settings = new QSettings(COMPANY_NAME, APP_NAME);
    LoadAndApplySettings();

    UpdateAppTitle();

    m_editMenu->setEnabled(false);
    m_saveAction->setEnabled(false);
    m_saveAsAction->setEnabled(false);

    if (argc > 1)
    {
        m_projectPath = QFileInfo(QString(argv[1])).absoluteFilePath();
    }
}

AmbMainWindow::~AmbMainWindow()
{
}

void AmbMainWindow::Associate(Project* proj)
{
    if (proj == m_project)
        return;

    if (m_project != NULL)
    {
        m_project->disconnect(this);
        disconnect(m_project);

        m_editMenu->setEnabled(false);
        m_saveAction->setEnabled(false);
        m_saveAsAction->setEnabled(false);

        m_copyLongAction->setChecked(false);
        m_copyShortAction->setChecked(false);
    }

    m_project = proj;
    PersistLocalPath();
    m_sceneEditDlg->Associate(m_project);
    m_sceneState->Associate(m_project);
    m_longFileDlg->Associate(m_project->StreamManager());
    m_shortFileDlg->Associate(m_project->SampleManager());

    if (m_project)
    {
        m_editMenu->setEnabled(true);
        m_saveAction->setEnabled(true);
        m_saveAsAction->setEnabled(true);

        m_copyLongAction->setChecked(m_project->StreamManager()->IsCopyLocalOn());
        m_copyShortAction->setChecked(m_project->SampleManager()->IsCopyLocalOn());

        connect(m_project, SIGNAL( Modified() ), this, SLOT( SetModified() ));
        connect(m_project, SIGNAL( destroyed() ), this, SLOT( RemoveProject() ));
    }

    UpdateAppTitle();
}

void AmbMainWindow::RemoveProject()
{
    m_project = NULL;
    m_projectPath = "";
    m_modified = false;
    m_curState = NULL;
    UpdateAppTitle();
}

void AmbMainWindow::RemoveCurrentState()
{
    m_curState = NULL;
}

void AmbMainWindow::closeEvent(QCloseEvent* evt)
{
    if (!CheckModified())
        evt->ignore();
    else
        evt->accept();
}

void AmbMainWindow::showEvent(QShowEvent* evt)
{
    evt->accept();

    if (!m_starting)
        return;
    m_starting = false;

    if (m_projectPath != "")
    {
        QString temp = m_projectPath;
        m_projectPath = "";
        LoadProject(temp);
    }

#ifndef _DEBUG
    if (m_projectPath == "")
        QTimer::singleShot(100, this, SLOT( OnStartup() ));
#endif
}

void AmbMainWindow::OnStartup()
{
    OpenOptionsDlg* dlg = new OpenOptionsDlg(m_recentFilesList, this);

    connect(dlg,  SIGNAL( OpenRecentSelected(const QString&) ),
            this, SLOT  ( LoadProject(const QString&)        ));
    connect(dlg,  SIGNAL( OpenOtherSelected()                ),
            this, SLOT  ( Load()                             ));
    connect(dlg,  SIGNAL( StartNewSelected()                 ),
            this, SLOT  ( NewProject()                       ));

    dlg->exec();
    delete dlg;
}

void AmbMainWindow::Load()
{
    if (!CheckModified())
        return;

    QString loadFilename =
        QFileDialog::getOpenFileName(
            this,
            "Load Project",
            QString(),
            "Ambience Sound Studio Project (*.assp)" );

    if (loadFilename != "")
    {
        LoadProject(loadFilename);
    }
}

void AmbMainWindow::LoadRecent()
{
    QAction* action = dynamic_cast<QAction*>(sender());
    if (!action)
        return;

    QString filename = m_recentFilesMap[action];

    LoadProject(filename);
}

void AmbMainWindow::Save()
{
    if (m_projectPath == "")
    {
        SaveAs();
        return;
    }
    if (!m_modified)
        return;

    SaveProject(m_projectPath);
}

void AmbMainWindow::SaveAs()
{
    QString saveFilename =
        QFileDialog::getSaveFileName(
            this,
            "Save Project As",
            QString(),
            "Ambience Sound Studio Project (*.assp)" );

    if (saveFilename != "")
    {
        SaveProject(saveFilename);
        PersistLocalPath();
    }
}

void AmbMainWindow::PersistLocalPath()
{
    if (m_projectPath == "")
    {
        m_project->StreamManager()->SetProjectPath("");
        m_project->SampleManager()->SetProjectPath("");
    }
    else if (m_project != NULL)
    {
        QFileInfo fileInfo(m_projectPath);
        m_project->StreamManager()->SetProjectPath(fileInfo.dir().absolutePath());
        m_project->SampleManager()->SetProjectPath(fileInfo.dir().absolutePath());
    }
}

void AmbMainWindow::NewProject()
{
    if (!CheckModified())
        return;

    m_sceneEditDlg->Associate(NULL);

    if (m_project)
        delete m_project;

    Associate(new Project);

    m_sceneEditDlg->exec();
}

void AmbMainWindow::LoadProject(const QString& filename)
{
    if (!CheckModified())
        return;

    QDomDocument doc("assp");
    QFile loadFile(filename);
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(
            this,
            "Failed load",
            "Could not read from the chosen file." );
        return;
    }
    if (!doc.setContent(&loadFile))
    {
        loadFile.close();
        return;
    }
    loadFile.close();

    QDomElement root = doc.documentElement();
    Project* newProj = NULL;
    try
    {
        newProj = LoadFromElement(filename, root);
    }
    catch (QException* e)
    {
        QMessageBox::critical(
            this,
            "Failed load",
            e->what() );
        return;
    }

    if (m_project)
        delete m_project;

    // do these in THIS ORDER
    m_projectPath = filename;
    Associate(newProj);

    AddToRecentProjectList(m_projectPath);
}

void AmbMainWindow::SaveProject(const QString& filename)
{
    QFile saveFile(filename);
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(
            this,
            "Failed save",
            "Could not write to the chosen file." );
        return;
    }

    QDomDocument doc("assp");
    SaveToElement(doc, m_project);
    saveFile.write(doc.toString().toAscii());
    saveFile.close();
    m_projectPath = filename;
    ClearModified();

    AddToRecentProjectList(m_projectPath);
}

void AmbMainWindow::SetModified()
{
    m_modified = true;
    UpdateAppTitle();
}

void AmbMainWindow::ClearModified()
{
    m_modified = false;
    UpdateAppTitle();
}

void AmbMainWindow::SelectSong()
{
    if (m_curState == NULL)
        throw QException("Programming Error: "
                         "Selecting song while not in a State!");

    A_SoundImport* import = m_longFileDlg->ExecSingleSelection();
    if (import == NULL)
        return;

    StartableSound* instance = new StartableSound(import);
    m_curState
        ->GetMusicController()
        ->AddInstance(instance);
}

void AmbMainWindow::SelectBackground()
{
    if (m_curState == NULL)
        throw QException("Programming Error: "
                         "Selecting a Background while not in a State!");

    QList<A_SoundImport*> imports = m_longFileDlg->ExecMultiSelection();

    for ( QList<A_SoundImport*>::iterator it = imports.begin();
          it != imports.end();
          it++ )
    {
        Background* instance = new Background(*it);
        m_curState
            ->GetBackgroundController()
            ->AddInstance(instance);
    }
}

void AmbMainWindow::SelectRandom()
{
    if (m_curState == NULL)
        throw QException("Programming Error: "
                         "Selecting a Random while not in a State!");

    QList<A_SoundImport*> imports = m_shortFileDlg->ExecMultiSelection();

    for ( QList<A_SoundImport*>::iterator it = imports.begin();
          it != imports.end();
          it++ )
    {
        RandomSound* instance = new RandomSound(*it);
        m_curState
            ->GetRandomController()
            ->AddInstance(instance);
    }
}

void AmbMainWindow::SelectInstant(int row, int col)
{
    if (m_curState == NULL)
        throw QException("Programming Error: "
                         "Adding a Soundboard entry while not in a State!");

    A_SoundImport* import = m_shortFileDlg->ExecSingleSelection();
    if (import == NULL)
        return;

    SoundboardInstance* instance = new SoundboardInstance(import);
    m_curState
        ->GetSoundboard()
        ->AddEntry(row, col, instance);
}

void AmbMainWindow::SwitchSceneState(Scene* newScene, State* newState)
{
    if (!m_project)
    {
        m_curState = NULL;
        m_musicCtrl->Associate(NULL);
        m_bgCtrl->Associate(NULL);
        m_randCtrl->Associate(NULL);
        return;
    }
    if (!newScene)
    {
        m_curState = NULL;
        m_musicCtrl->Associate(NULL);
        m_bgCtrl->Associate(NULL);
        m_randCtrl->Associate(NULL);
        return;
    }
    if (!newState)
    {
        m_curState = NULL;
        m_musicCtrl->Associate(NULL);
        m_bgCtrl->Associate(NULL);
        m_randCtrl->Associate(NULL);
        return;
    }
    if (newState == m_curState)
        return;

    bool sharedMusic = false;
    StartableSound* curSong;
    QList<A_SoundInstance*> sharedBg;
    if (m_curState)
    {
        MusicCtrl* curMusic = m_curState->GetMusicController();
        MasterCtrl* curBg = m_curState->GetBackgroundController();
        MasterCtrl* curRand = m_curState->GetRandomController();

        if (newState)
        {
            MusicCtrl* newMusic = newState->GetMusicController();
            MasterCtrl* newBg = newState->GetBackgroundController();

            sharedMusic = curMusic->SharesCurrentSongWith(*newMusic);
            sharedBg = curBg->SharedWith(*newBg);

            if (sharedMusic)
                curSong = curMusic->CurrentSong();
        }

        curMusic->Suspend();
        curBg->Suspend();
        curRand->Suspend();
    }

    MusicCtrl* newMusic = newState->GetMusicController();
    MasterCtrl* newBg = newState->GetBackgroundController();
    MasterCtrl* newRand = newState->GetRandomController();
    Soundboard* newBoard = newState->GetSoundboard();

    newMusic->Resume();
    newBg->Resume();
    newRand->Resume();

    m_musicCtrl->Associate(newMusic);
    m_bgCtrl->Associate(newBg);
    m_randCtrl->Associate(newRand);
    m_sndboardObj->Associate(newBoard);

    m_curState = newState;

    connect(newState,   SIGNAL( destroyed()             ),
            this,       SLOT  ( RemoveCurrentState()    ) );
}

void AmbMainWindow::ShowAboutDlg()
{
    QDialog dlg;
    Ui::AboutDlgUi dlgLayout;
    dlgLayout.setupUi(&dlg);

    QString text = dlgLayout.m_text->text();
    text.replace("%product_string%", QString("%1 (%2)").arg(APP_NAME).arg(VersionString()));
    dlgLayout.m_text->setText(text);

    dlg.exec();
}

void AmbMainWindow::SetCopyLocal(bool copy)
{
    QAction* activator = dynamic_cast<QAction*>(sender());
    if (!activator)
        return;

    if (copy && m_projectPath == "")
    {
        QMessageBox::StandardButton result =
            QMessageBox::question(
                this,
                QString("Save Project"),
                QString("The project must be saved to activate this feature.\n"
                        "Do you wish to save?"),
                ( QMessageBox::Yes | QMessageBox::No ),
                QMessageBox::Yes );

        if (result == QMessageBox::No)
        {
            activator->setChecked(false);
            return;
        }

        SaveAs();
        if (m_projectPath == "")
        {
            activator->setChecked(false);
            return;
        }
    }

    A_ImportManager* importMgr =
        (activator == m_copyLongAction)?(m_project->StreamManager()):(
        (activator == m_copyShortAction)?(m_project->SampleManager()):(NULL) );
    if (importMgr)
    {
        importMgr->SetCopyLocal(copy);
    }
}

void AmbMainWindow::AddToRecentProjectList(const QString& filename)
{
    QStringList::iterator it;
    for ( it = m_recentFilesList.begin();
          it != m_recentFilesList.end();
          it++ )
    {
        if ((*it) == filename)
            break;
    }

    if (it != m_recentFilesList.end())
        m_recentFilesList.erase(it);

    m_recentFilesList.prepend(filename);

    if (m_recentFilesList.size() > RECENT_FILES_LIST_MAX)
        m_recentFilesList.removeLast();

    m_settings->beginGroup("Application");
    m_settings->setValue("RecentFiles", m_recentFilesList);
    m_settings->endGroup();

    PutRecentProjectListOnMenu();
}

void AmbMainWindow::PutRecentProjectListOnMenu()
{
    m_recentFilesMenu->clear();
    m_recentFilesMap.clear();

    for ( QStringList::iterator it = m_recentFilesList.begin();
          it != m_recentFilesList.end();
          it++ )
    {
        QAction* action = m_recentFilesMenu->addAction(*it);
        if (!action)
            continue;

        m_recentFilesMap[action] = (*it);

        connect(action, SIGNAL( triggered() ), this, SLOT( LoadRecent() ));
    }
}

void AmbMainWindow::LoadAndApplySettings()
{
    if (!m_settings)
        return;

    m_settings->beginGroup("MainWidget");
    m_settings->endGroup();

    m_settings->beginGroup("Application");
    m_recentFilesList = m_settings->value("RecentFiles", m_recentFilesList).toStringList();
    m_settings->endGroup();
    PutRecentProjectListOnMenu();
}

Project* AmbMainWindow::LoadFromElement(const QString& filename, const QDomElement& root)
{
    if (root.tagName() != "ambience")
        throw QException("Not an Ambience file.");

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

        if (child.tagName() == "limports" && longImports.isNull())
            longImports = child;
        else if (child.tagName() == "simports" && shortImports.isNull())
            shortImports = child;
        else if (child.tagName() == "project" && project.isNull())
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
        throw QException(errorMsg);
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

void AmbMainWindow::LoadStreamImportList(
    Project* parent,
    const QDomElement& longImports )
{
    bool copyLocal = longImports.attribute("copyLocal", "0").toInt();
    parent->StreamManager()->SetCopyLocal(copyLocal);

    for( QDomNode n = longImports.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement file = n.toElement();
        if ( file.isNull() || file.tagName() != "file" )
            continue;

        QString fileTitle = file.attribute("title", "");
        QString filePath = file.attribute("path", "");

        parent->StreamManager()->ImportFile(fileTitle, filePath);
    }
}

void AmbMainWindow::LoadSampleImportList(
    Project* parent,
    const QDomElement& shortImports )
{
    bool copyLocal = shortImports.attribute("copyLocal", "0").toInt();
    parent->SampleManager()->SetCopyLocal(copyLocal);

    for( QDomNode n = shortImports.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement file = n.toElement();
        if ( file.isNull() || file.tagName() != "file" )
            continue;

        QString fileTitle = file.attribute("title", "");
        QString filePath = file.attribute("path", "");

        parent->SampleManager()->ImportFile(fileTitle, filePath);
    }
}

void AmbMainWindow::LoadProjectBody(Project* proj, const QDomElement& project)
{
    for( QDomNode n = project.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement scene = n.toElement();
        if ( scene.isNull() || scene.tagName() != "scene")
            throw QException("Improperly formatted Project body.");

        QString sceneTitle = scene.attribute("title", "");

        Scene* newScene = new Scene(sceneTitle);
        proj->AddScene(newScene);
        LoadScene(proj, newScene, scene);
    }
}

void AmbMainWindow::LoadScene(
    Project* proj,
    Scene* newScene,
    const QDomElement& scene )
{
    for( QDomNode n = scene.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement state = n.toElement();
        if ( state.isNull() || state.tagName() != "state")
            throw QException("Improperly formatted Scene data");

        QString stateTitle = state.attribute("title", "");
        State* newState = new State(stateTitle);
        newScene->AddState(newState);
        LoadState(proj, newState, state);
    }
}

void AmbMainWindow::LoadState(
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
            throw QException("Improperly formatted State data.");

        if (child.tagName() == "music")
        {
            if (!musicData.isNull())
                throw QException("Cannot have multiple Music data sections.");
            musicData = child;
        }
        else if (child.tagName() == "background")
        {
            if (!bgData.isNull())
                throw
                    QException("Cannot have multiple Background data sections.");
            bgData = child;
        }
        else if (child.tagName() == "random")
        {
            if (!randData.isNull())
                throw QException("Cannot have multiple Random data sections.");
            randData = child;
        }
        else if (child.tagName() == "soundboard")
        {
            if (!sndboardData.isNull())
                throw QException("Cannot have multiple Soundboard data sections.");
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
        throw QException(errorMsg);
    }

    LoadMusicData(proj, newState, musicData);
    LoadBackgroundData(proj, newState, bgData);
    LoadRandomData(proj, newState, randData);
    LoadSoundboardData(proj, newState, sndboardData);
}

void AmbMainWindow::LoadMusicData(
    Project* proj,
    State* parent,
    const QDomElement& musicData )
{
    MusicCtrl* ctrl = parent->GetMusicController();

    QString vol = musicData.attribute("vol", "0");
    QString mute = musicData.attribute("mute", "0");

    ctrl->SetVolume(vol.toInt());
    ctrl->SetPaused(mute.toInt());
    for( QDomNode n = musicData.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement song = n.toElement();
        if ( song.isNull() || song.tagName() != "song" )
            throw QException("Improperly formatted Music section.");

        QString songTitle = song.attribute("title", "");
        StartableSound* newSong = new StartableSound(
            proj->StreamManager()->GetImport(songTitle)
            );
        ctrl->AddInstance(newSong);
    }
}

void AmbMainWindow::LoadBackgroundData(
    Project* proj,
    State* parent,
    const QDomElement& bgData )
{
    MasterCtrl* ctrl = parent->GetBackgroundController();

    QString vol = bgData.attribute("vol", "0");
    QString mute = bgData.attribute("mute", "0");

    ctrl->SetVolume(vol.toInt());
    ctrl->SetPaused(mute.toInt());
    for( QDomNode n = bgData.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement sound = n.toElement();
        if ( sound.isNull() || sound.tagName() != "sound" )
            throw QException("Improperly formatted Background section.");

        QString soundTitle = sound.attribute("title", "");
        Background* newBg = new Background(
            proj->StreamManager()->GetImport(soundTitle)
            );
        ctrl->AddInstance(newBg);

        QString soundVol = sound.attribute("vol", "0");
        QString soundMute = sound.attribute("mute", "0");

        newBg->SetInstanceVolume(soundVol.toInt());
        newBg->SetInstancePaused(soundMute.toInt());
    }
}

void AmbMainWindow::LoadRandomData(
    Project* proj,
    State* parent,
    const QDomElement& randData )
{
    MasterCtrl* ctrl = parent->GetRandomController();

    QString vol = randData.attribute("vol", "0");
    QString mute = randData.attribute("mute", "0");

    ctrl->SetVolume(vol.toInt());
    ctrl->SetPaused(mute.toInt());
    for( QDomNode n = randData.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement effect = n.toElement();
        if ( effect.isNull() || effect.tagName() != "effect" )
            throw QException("Improperly formatted Random section.");

        QString effectTitle = effect.attribute("title", "");
        RandomSound* newRand = new RandomSound(
            proj->SampleManager()->GetImport(effectTitle)
            );
        ctrl->AddInstance(newRand);

        QString effectVol = effect.attribute("vol", "0");
        QString effectPer = effect.attribute("per", "0");
        QString effectPerType = effect.attribute("perType", "1");
        QString effectVar = effect.attribute("var", "0");
        QString effectMute = effect.attribute("mute", "0");

        newRand->SetInstanceVolume(effectVol.toInt());
        newRand->SetPeriod(effectPer.toDouble());
        newRand->SetPeriodType(
            RandomSound::PeriodTypes[ effectPerType.toInt() ]
            );
        newRand->SetVariance(effectVar.toInt());
        newRand->SetInstancePaused(effectMute.toInt());
    }
}

void AmbMainWindow::LoadSoundboardData(
    Project* proj,
    State* parent,
    const QDomElement& sndboardData )
{
    Soundboard* sndboard = parent->GetSoundboard();

    QString vol = sndboardData.attribute("vol", "0");
    QString rows = sndboardData.attribute("rows", "1");
    QString cols = sndboardData.attribute("cols", "1");

    sndboard->SetVolume(vol.toInt());
    sndboard->Resize(rows.toInt(), cols.toInt());
    for( QDomNode n = sndboardData.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement effect = n.toElement();
        if ( effect.isNull() || effect.tagName() != "effect" )
            continue;

        QString effectTitle = effect.attribute("title", "");
        QString effectRow = effect.attribute("row", "-1");
        QString effectCol = effect.attribute("col", "-1");

        SoundboardInstance* instance = new SoundboardInstance(
            proj->SampleManager()->GetImport(effectTitle)
            );
        sndboard->AddEntry(effectRow.toInt(), effectCol.toInt(), instance);
    }
}

void AmbMainWindow::SaveToElement(QDomDocument& doc, Project* proj)
{
    QDomElement root = doc.createElement("ambience");
    root.setAttribute("ver", VersionString());

    SaveStreamImportList(root, proj->StreamManager());
    SaveSampleImportList(root, proj->SampleManager());
    SaveProjectBody(root, proj);

    doc.appendChild(root);
}

void AmbMainWindow::SaveStreamImportList(QDomElement& parent, A_ImportManager* mgr)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement limports = doc.createElement("limports");

    SaveImportList(limports, mgr);

    parent.appendChild(limports);
}

void AmbMainWindow::SaveSampleImportList(QDomElement& parent, A_ImportManager* mgr)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement simports = doc.createElement("simports");

    SaveImportList(simports, mgr);

    parent.appendChild(simports);
}

void AmbMainWindow::SaveImport(QDomElement& parent, A_SoundImport* import)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement file = doc.createElement("file");

    file.setAttribute("title", import->Title());
    file.setAttribute("path", import->Filename());

    parent.appendChild(file);
}

void AmbMainWindow::SaveImportList(QDomElement& element, A_ImportManager* mgr)
{
    element.setAttribute("copyLocal", (int)mgr->IsCopyLocalOn());

    const QList<A_SoundImport*>& importList = mgr->ImportList();
    for ( QList<A_SoundImport*>::const_iterator it = importList.begin();
          it != importList.end();
          it++ )
    {
        SaveImport(element, *it);
    }
}

void AmbMainWindow::SaveProjectBody(QDomElement& parent, Project* proj)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement project = doc.createElement("project");

    const QList<Scene*>& sceneList = proj->SceneList();
    for ( QList<Scene*>::const_iterator it = sceneList.begin();
          it != sceneList.end();
          it++ )
    {
        SaveScene(project, *it);
    }

    parent.appendChild(project);
}

void AmbMainWindow::SaveScene(QDomElement& parent, Scene* scene)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement sceneEl = doc.createElement("scene");

    sceneEl.setAttribute("title", scene->Title());

    const QList<State*>& stateList = scene->StateList();
    for ( QList<State*>::const_iterator it = stateList.begin();
          it != stateList.end();
          it++ )
    {
        SaveState(sceneEl, *it);
    }

    parent.appendChild(sceneEl);
}

void AmbMainWindow::SaveState(QDomElement& parent, State* state)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement stateEl = doc.createElement("state");

    stateEl.setAttribute("title", state->Title());

    SaveMusicData(stateEl, state->GetMusicController());
    SaveBackgroundData(stateEl, state->GetBackgroundController());
    SaveRandomData(stateEl, state->GetRandomController());
    SaveSoundboardData(stateEl, state->GetSoundboard());

    parent.appendChild(stateEl);
}

void AmbMainWindow::SaveMusicData(QDomElement& parent, MusicCtrl* musicCtrl)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement music = doc.createElement("music");

    music.setAttribute("vol", QString("%1").arg(musicCtrl->Volume()));
    music.setAttribute("mute", QString("%1").arg((int)musicCtrl->IsPaused()));

    const QList<A_SoundInstance*>& songList = musicCtrl->Children();
    for ( QList<A_SoundInstance*>::const_iterator it = songList.begin();
          it != songList.end();
          it++ )
    {
        SaveSong(music, *it);
    }

    parent.appendChild(music);
}

void AmbMainWindow::SaveBackgroundData(QDomElement& parent, MasterCtrl* bgCtrl)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement background = doc.createElement("background");

    background.setAttribute("vol", QString("%1").arg(bgCtrl->Volume()));
    background.setAttribute("mute", QString("%1").arg((int)bgCtrl->IsPaused()));

    const QList<A_SoundInstance*>& soundList = bgCtrl->Children();
    for ( QList<A_SoundInstance*>::const_iterator it = soundList.begin();
          it != soundList.end();
          it++ )
    {
        SaveBackground(background, *it);
    }

    parent.appendChild(background);
}

void AmbMainWindow::SaveRandomData(QDomElement& parent, MasterCtrl* randCtrl)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement random = doc.createElement("random");

    random.setAttribute("vol", QString("%1").arg(randCtrl->Volume()));
    random.setAttribute("mute", QString("%1").arg((int)randCtrl->IsPaused()));

    const QList<A_SoundInstance*>& effectList = randCtrl->Children();
    for ( QList<A_SoundInstance*>::const_iterator it = effectList.begin();
          it != effectList.end();
          it++ )
    {
        SaveRandomSound(random, dynamic_cast<RandomSound*>(*it));
    }

    parent.appendChild(random);
}

void AmbMainWindow::SaveSoundboardData(QDomElement& parent, Soundboard* sndboard)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement soundboard = doc.createElement("soundboard");

    soundboard.setAttribute("vol", QString("%1").arg(sndboard->Volume()));
    soundboard.setAttribute("rows", QString("%1").arg(sndboard->RowCount()));
    soundboard.setAttribute("cols", QString("%1").arg(sndboard->ColCount()));

    const Soundboard::SoundGrid& soundGrid = sndboard->GetSoundGrid();
    for ( Soundboard::SoundGrid::const_iterator it = soundGrid.begin();
          it != soundGrid.end();
          it++ )
    {
        SaveSong(soundboard, it.value());
    }

    parent.appendChild(soundboard);
}

void AmbMainWindow::SaveSong(QDomElement& parent, A_SoundInstance* instance)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement song = doc.createElement("song");

    song.setAttribute("title", instance->Title());

    parent.appendChild(song);
}

void AmbMainWindow::SaveBackground(QDomElement& parent, A_SoundInstance* instance)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement sound = doc.createElement("sound");

    sound.setAttribute("title", instance->Title());
    sound.setAttribute(
        "vol",
        QString("%1")
            .arg( instance->InstanceVolume() ) );
    sound.setAttribute(
        "mute",
        QString("%1")
            .arg( (int)instance->IsInstancePaused() ) );

    parent.appendChild(sound);
}

void AmbMainWindow::SaveRandomSound(QDomElement& parent, RandomSound* instance)
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement effect = doc.createElement("effect");

    effect.setAttribute("title", instance->Title());
    effect.setAttribute(
        "vol",
        QString("%1")
            .arg( instance->InstanceVolume() ) );
    effect.setAttribute(
        "per",
        QString("%1")
            .arg( instance->Period() ) );
    effect.setAttribute(
        "perType",
        QString("%1")
            .arg( (int)instance->GetPeriodType() ) );
    effect.setAttribute(
        "var",
        QString("%1")
            .arg( instance->Variance() ) );
    effect.setAttribute(
        "mute",
        QString("%1")
            .arg( (int)instance->IsInstancePaused() ) );

    parent.appendChild(effect);
}

void AmbMainWindow::SaveSoundboardEffect(
    QDomElement& parent,
    Soundboard::SoundGrid::const_iterator soundGridIt )
{
    QDomDocument doc = parent.ownerDocument();
    QDomElement effect = doc.createElement("effect");

    effect.setAttribute("row", QString("%1").arg(soundGridIt.key().first));
    effect.setAttribute("col", QString("%1").arg(soundGridIt.key().second));
    effect.setAttribute("title", soundGridIt.value()->Title());

    parent.appendChild(effect);
}

bool AmbMainWindow::CheckModified()
{
    if (m_modified)
    {
        QMessageBox::StandardButton result =
            QMessageBox::warning( this, "Save changes?",
                "The current project has unsaved changes.\n"
                "Would you like to save now?\n"
                "(Choosing No will lose all changes.)",
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                QMessageBox::Cancel );

        if (result == QMessageBox::Cancel)
            return false;
        else if (result == QMessageBox::Yes)
            Save();
    }

    return true;
}

void AmbMainWindow::UpdateAppTitle()
{
    QString title = APP_NAME;
#ifdef _DEBUG
    title += " (";
    title += VersionString();
    title += ")";
#endif
    title += " - ";
    if (m_projectPath == "")
        title += "Untitled";
    else
        title += ProjectTitle(m_projectPath);

    if (m_modified)
        title += "*";

    setWindowTitle(title);
}

QString AmbMainWindow::VersionString()
{
    unsigned int MM = (VERSION_CODE >> 24) & 0xFF;
    unsigned int Mm = (VERSION_CODE >> 16) & 0xFF;
    unsigned int mm = (VERSION_CODE >> 8 ) & 0xFF;
    bool beta       = (VERSION_CODE & 0xFF);

    return QString(VERSION_FORMAT)
        .arg(MM).arg(Mm).arg(mm, 2, 10, QLatin1Char('0'))
        .arg(beta?" beta":"");
}

QString AmbMainWindow::ProjectTitle(const QString& filename)
{
    QFileInfo fi(filename);
    return fi.completeBaseName();
}
