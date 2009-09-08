#include <stdexcept>

#include <QCloseEvent>
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
#include "ProjectFileAdapter.h"
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

    connect( m_musicCtrl,       SIGNAL( AddSelected(I_ImportTarget*)            ),
             m_longFileDlg,     SLOT  ( ExecSingleSelection(I_ImportTarget*)    ) );
    connect( m_bgCtrl,          SIGNAL( AddSelected(I_ImportTarget*)            ),
             m_longFileDlg,     SLOT  ( ExecMultiSelection(I_ImportTarget*)     ) );
    connect( m_randCtrl,        SIGNAL( AddSelected(I_ImportTarget*)            ),
             m_shortFileDlg,    SLOT  ( ExecMultiSelection(I_ImportTarget*)     ) );
    connect( m_sndboardObj,     SIGNAL( SoundRequested(I_ImportTarget*)         ),
             m_shortFileDlg,    SLOT  ( ExecSingleSelection(I_ImportTarget*)    ) );

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

    QFile loadFile(filename);
    Project* newProj = NULL;
    try
    {
        ProjectFileAdapter adapter;
        newProj = adapter.CreateProjectFromFile(loadFile);
    }
    catch (const std::runtime_error& e)
    {
        QMessageBox::critical(
            this,
            "Failed load",
            e.what() );
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
    ProjectFileAdapter adapter;
    adapter.SaveProjectToFile(m_project, VersionString(), saveFile);

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
