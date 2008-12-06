#include <QCloseEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QMap>
#include <QMessageBox>
#include <QSettings>
#include <QShowEvent>
#include <QTimer>

#include "AboutDlgUi.h"
#include "AmbMainWidget.h"
#include "BackgroundCtrl.h"
#include "FileSelectionDlg.h"
#include "MusicCtrl.h"
#include "OpenOptionsDlg.h"
#include "Project.h"
#include "RandomCtrl.h"
#include "Scene.h"
#include "SceneEditorDlg.h"
#include "Soundboard.h"
#include "SoundMaster.h"
#include "State.h"

#include "AmbMainWindow.h"


const unsigned int  AmbMainWindow::VERSION_CODE             = 0x01010301;
const char          AmbMainWindow::APP_NAME[]               = "Ambience Sound Studio";
const char          AmbMainWindow::COMPANY_NAME[]           = "MeiCor Gaming";
const int           AmbMainWindow::RECENT_FILES_LIST_MAX    = 4;

AmbMainWindow::AmbMainWindow(int argc, char* argv[], QWidget* parent)
:   QMainWindow(parent),
    m_mainWidgetLayout(NULL),
    m_mainWidget(NULL),
    m_project(NULL),
    m_projectPath(""),
    m_modified(false),
    m_sceneEditDlg(NULL),
    m_longFileDlg(NULL),
    m_shortFileDlg(NULL),
    m_starting(true),
    m_settings(NULL)
{
    setupUi(this);

    // Create all children.
    m_mainWidgetLayout = new QHBoxLayout;
    m_mainWidget = new AmbMainWidget;
    m_sceneEditDlg = new SceneEditorDlg(this);
    m_longFileDlg = new FileSelectionDlg(this);
    m_shortFileDlg = new FileSelectionDlg(this);

    // Setup layout.
    m_mainWidgetFrm->setLayout(m_mainWidgetLayout);

    // Setup main widget.
    m_mainWidgetLayout->addWidget(m_mainWidget);

    // Setup file dialogs.
    m_longFileDlg->setWindowTitle("Streamed file Import");
    m_shortFileDlg->setWindowTitle("Sampled file Import");

    // Connect signals.
    connect(m_newAction, SIGNAL( activated() ), this, SLOT( NewProject() ));
    connect(m_openAction, SIGNAL( activated() ), this, SLOT( Load() ));
    connect(m_saveAction, SIGNAL( activated() ), this, SLOT( Save() ));
    connect(m_saveAsAction, SIGNAL( activated() ), this, SLOT( SaveAs() ));
    connect(m_scenesAction, SIGNAL( activated() ), m_sceneEditDlg, SLOT( exec() ));
    connect(m_longAction, SIGNAL( activated() ), m_longFileDlg, SLOT( ExecNoSelection() ));
    connect(m_shortAction, SIGNAL( activated() ), m_shortFileDlg, SLOT( ExecNoSelection() ));
    connect(m_aboutAction, SIGNAL( activated() ), this, SLOT( ShowAboutDlg() ));

    connect(m_sceneCbo, SIGNAL( currentIndexChanged(const QString&) ),
            this,       SLOT  ( UpdateStateList()                   ));
    connect(m_switchBtn, SIGNAL( clicked() ), this, SLOT( SwitchSceneState() ));

    connect( m_longFileDlg,  SIGNAL( ImportRequested(const QString&, const QString&)  ),
             this,           SLOT  ( ImportStreamFile(const QString&, const QString&) ) );
    connect( m_longFileDlg,  SIGNAL( DeleteRequested(const QString&)                  ),
             this,           SLOT  ( CloseStreamFile(const QString&)                  ) );

    connect( m_shortFileDlg, SIGNAL( ImportRequested(const QString&, const QString&)  ),
             this,           SLOT  ( ImportSampleFile(const QString&, const QString&) ) );
    connect( m_shortFileDlg, SIGNAL( DeleteRequested(const QString&)                  ),
             this,           SLOT  ( CloseSampleFile(const QString&)                  ) );

    connect( m_sceneEditDlg, SIGNAL( accepted()        ),
             this,           SLOT  ( UpdateSceneList() ) );

    connect( m_mainWidget,  SIGNAL( AddSongSelected()                   ),
             this,          SLOT  ( SelectSong()                        ) );
    connect( m_mainWidget,  SIGNAL( AddBackgroundSelected()             ),
             this,          SLOT  ( SelectBackground()                  ) );
    connect( m_mainWidget,  SIGNAL( AddRandomSelected()                 ),
             this,          SLOT  ( SelectRandom()                      ) );
    connect( m_mainWidget,  SIGNAL( AddInstantSelected(int,int)         ),
             this,          SLOT  ( SelectInstant(int,int)              ) );
    connect( m_mainWidget,  SIGNAL( ExpandLeftToggled(bool)             ),
             this,          SLOT  ( ApplyWidgetExpandLeftSetting(bool)  ) );

    // Apply settings.
    m_settings = new QSettings(COMPANY_NAME, APP_NAME);
    LoadAndApplySettings();

    UpdateAppTitle();

    if (argc > 1)
    {
        m_projectPath = QFileInfo(QString(argv[1])).absoluteFilePath();
    }
}

AmbMainWindow::~AmbMainWindow()
{
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

    if (m_projectPath == "")
        QTimer::singleShot(100, this, SLOT( OnStartup() ));
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
    }
}

void AmbMainWindow::NewProject()
{
    if (!CheckModified())
        return;

    m_mainWidget->Associate(NULL);
    m_sceneEditDlg->Associate(NULL);

    if (m_project)
    {
        delete m_project;
        m_project = NULL;
        m_projectPath = "";
    }

    m_project = new Project;
    m_modified = false;
    m_sceneEditDlg->Associate(m_project);
    m_sceneCbo->setModel(m_project->Model());
    connect(m_project, SIGNAL( Modified() ), this, SLOT( SetModified() ));
    UpdateAppTitle();

    m_sceneEditDlg->exec();
}

void AmbMainWindow::LoadProject(const QString& filename)
{
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
    if (root.tagName() != "ambience")
    {
        QMessageBox::critical(
            this,
            "Failed load",
            "The file is invalid." );
        return;
    }

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

    if (longImports.isNull() || shortImports.isNull() || project.isNull())
    {
        QMessageBox::critical(
            this,
            "Failed load",
            "The file is invalid." );
        return;
    }

    m_mainWidget->Associate(NULL);
    m_sceneEditDlg->Associate(NULL);

    if (m_project)
    {
        delete m_project;
        m_project = NULL;
    }

    SoundMaster::Shutdown();

    // do these in THIS ORDER
    LoadStreamImportList(longImports);
    LoadSampleImportList(shortImports);
    m_project = new Project(project);

    m_sceneEditDlg->Associate(m_project);
    m_sceneCbo->setModel(m_project->Model());
    UpdateStateList();
    connect(m_project, SIGNAL( Modified() ), this, SLOT( SetModified() ));
    m_projectPath = filename;
    ClearModified();

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
    QDomElement root = doc.createElement("ambience");
    root.setAttribute("ver", VersionString());
    doc.appendChild(root);

    QDomElement longImports = doc.createElement("limports");
    root.appendChild(longImports);
    const QMap<QString, QString>& longFileMap =
        m_longFileDlg->GetFileMap();
    for ( QMap<QString, QString>::const_iterator longIt = longFileMap.begin();
          longIt != longFileMap.end();
          longIt++ )
    {
        QDomElement filename = doc.createElement("file");
        filename.setAttribute("title", longIt.key());
        filename.setAttribute("path", longIt.value());
        longImports.appendChild(filename);
    }

    QDomElement shortImports = doc.createElement("simports");
    root.appendChild(shortImports);
    const QMap<QString, QString>& shortFileMap =
        m_shortFileDlg->GetFileMap();
    for ( QMap<QString, QString>::const_iterator shortIt = shortFileMap.begin();
          shortIt != shortFileMap.end();
          shortIt++ )
    {
        QDomElement filename = doc.createElement("file");
        filename.setAttribute("title", shortIt.key());
        filename.setAttribute("path", shortIt.value());
        shortImports.appendChild(filename);
    }

    QDomElement project = doc.createElement("project");
    m_project->WriteData(project);
    root.appendChild(project);

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

void AmbMainWindow::ImportStreamFile(const QString& title, const QString& filename)
{
    SoundMaster& master = SoundMaster::Get();

    if (!master.ImportStream(filename, title))
    {
        QMessageBox::critical(
            this,
            QString("Import Error"),
            QString("\"") +
                filename +
                QString("\" could not be imported.") );
    }
    else
    {
        m_longFileDlg->AddFile(title, filename);
        SetModified();
    }
}

void AmbMainWindow::ImportSampleFile(const QString& title, const QString& filename)
{
    SoundMaster& master = SoundMaster::Get();

    if (!master.ImportSample(filename, title))
    {
        QMessageBox::critical(
            this,
            QString("Import Error"),
            QString("\"") +
                filename +
                QString("\" could not be imported.") );
    }
    else
    {
        m_shortFileDlg->AddFile(title, filename);
        SetModified();
    }
}

void AmbMainWindow::CloseStreamFile(const QString& title)
{
    SoundMaster& master = SoundMaster::Get();

    master.CloseStream(title);
    m_longFileDlg->DeleteFile(title);
    SetModified();
}

void AmbMainWindow::CloseSampleFile(const QString& title)
{
    SoundMaster& master = SoundMaster::Get();

    master.CloseSample(title);
    m_shortFileDlg->DeleteFile(title);
    SetModified();
}

void AmbMainWindow::SelectSong()
{
    QString songTitle = m_longFileDlg->ExecSingleSelection();

    if (songTitle != "" && m_mainWidget->CurrentState())
        m_mainWidget
            ->CurrentState()
            ->GetMusicController()
            ->AddSong(songTitle);
}

void AmbMainWindow::SelectBackground()
{
    QStringList bgTitles = m_longFileDlg->ExecMultiSelection();

    for ( QStringList::iterator it = bgTitles.begin();
          it != bgTitles.end();
          it++ )
    {
        if (m_mainWidget->CurrentState())
            m_mainWidget
                ->CurrentState()
                ->GetBackgroundController()
                ->AddBackground(*it);
    }
}

void AmbMainWindow::SelectRandom()
{
    QStringList randTitles = m_shortFileDlg->ExecMultiSelection();

    for ( QStringList::iterator it = randTitles.begin();
          it != randTitles.end();
          it++ )
    {
        if (m_mainWidget->CurrentState())
            m_mainWidget
                ->CurrentState()
                ->GetRandomController()
                ->AddRandom(*it);
    }
}

void AmbMainWindow::SelectInstant(int row, int col)
{
    QString title = m_shortFileDlg->ExecSingleSelection();

    if (title != "" && m_mainWidget->CurrentState())
        m_mainWidget
            ->CurrentState()
            ->GetSoundboard()
            ->AddEntry(row, col, title);
}

void AmbMainWindow::UpdateSceneList()
{
    if (!m_project)
        return;

   m_sceneCbo->setModel(m_project->Model());
   UpdateStateList();
}

void AmbMainWindow::UpdateStateList()
{
    if (!m_project)
        return;

    Scene* curScene = m_project->GetScene(m_sceneCbo->currentText());
    if (curScene)
        m_stateCbo->setModel(curScene->Model());
}

void AmbMainWindow::SwitchSceneState()
{
    if (!m_project)
        return;

    Scene* curScene = m_project->GetScene(m_sceneCbo->currentText());
    if (!curScene)
        return;

    State* curState = curScene->GetState(m_stateCbo->currentText());
    if (!curState)
        return;

    m_mainWidget->Associate(curState);
}

void AmbMainWindow::ApplyWidgetExpandLeftSetting(bool expand)
{
    if (!m_settings)
        return;

    m_settings->beginGroup("MainWidget");
    m_settings->setValue("ExpandLeft", expand);
    m_settings->endGroup();
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

        connect(action, SIGNAL( activated() ), this, SLOT( LoadRecent() ));
    }
}

void AmbMainWindow::LoadAndApplySettings()
{
    if (!m_settings)
        return;

    m_settings->beginGroup("MainWidget");
    m_mainWidget->ExpandLeft(m_settings->value("ExpandLeft", (bool)false).toBool());
    m_settings->endGroup();

    m_settings->beginGroup("Application");
    m_recentFilesList = m_settings->value("RecentFiles", m_recentFilesList).toStringList();
    m_settings->endGroup();
    PutRecentProjectListOnMenu();
}

void AmbMainWindow::LoadStreamImportList(const QDomElement& longImports)
{
    for( QDomNode n = longImports.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement file = n.toElement();
        if ( file.isNull() || file.tagName() != "file" )
            continue;

        QString fileTitle = file.attribute("title", "");
        QString filePath = file.attribute("path", "");

        ImportStreamFile(fileTitle, filePath);
    }
}

void AmbMainWindow::LoadSampleImportList(const QDomElement& shortImports)
{
    for( QDomNode n = shortImports.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement file = n.toElement();
        if ( file.isNull() || file.tagName() != "file" )
            continue;

        QString fileTitle = file.attribute("title", "");
        QString filePath = file.attribute("path", "");

        ImportSampleFile(fileTitle, filePath);
    }
}

bool AmbMainWindow::CheckModified()
{
    if (m_modified)
    {
        QMessageBox::StandardButton result =
            QMessageBox::warning( this, "Save changes?",
                "The current project has unsaved changes.\n"
                "Would you like to save now?",
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
    char retval[32];

    unsigned int MM = (VERSION_CODE >> 24) & 0xFF;
    unsigned int Mm = (VERSION_CODE >> 16) & 0xFF;
    unsigned int mm = (VERSION_CODE >> 8 ) & 0xFF;
    bool beta       = (VERSION_CODE & 0xFF);

    sprintf(retval, "%d.%d rev %02d%s", MM, Mm, mm, (beta?" beta":""));

    return retval;
}

QString AmbMainWindow::ProjectTitle(const QString& filename)
{
    QFileInfo fi(filename);
    return fi.completeBaseName();
}
