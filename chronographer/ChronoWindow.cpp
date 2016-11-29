#include <QCloseEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include "ChronoProject.qoh"
#include "ProjectSetupView.qoh"
#include "Session.h"
#include "SessionView.qoh"
#include "XmlSerialDocument.h"
#include "XmlSerialElement.h"

#include "ChronoWindow.qoh"


ChronoWindow::ChronoWindow()
:   _modifiedFlag( false ),
    _project( NULL ),
    _session( NULL ),
    _setupView( NULL ),
    _sessionView( NULL )
{
    setupUi(this);

    connect(_actFileNew, SIGNAL( triggered() ), this, SLOT( NewProject() ));
    connect(_actFileLoad, SIGNAL( triggered() ), this, SLOT( LoadProject() ));
    connect(_actFileSave, SIGNAL( triggered() ), this, SLOT( SaveProject() ));
    connect(_actFileSaveAs, SIGNAL( triggered() ), this, SLOT( SaveProjectAs() ));

    connect(_actProjectBeginSession, SIGNAL( triggered() ), this, SLOT( BeginSession() ) );
}

ChronoWindow::~ChronoWindow()
{
    if ( _project != NULL )
        delete _project;
}

void ChronoWindow::NewProject()
{
    if ( !CheckSaveAndClean() )
        return;

    _modifiedFlag = false;
    _project = new ChronoProject();
    connect( _project, SIGNAL( Modified() ), this, SLOT( OnModified() ) );

    _projectFilename = "";
    _setupView = new ProjectSetupView(_project);
    setCentralWidget(_setupView);
}

void ChronoWindow::LoadProject()
{
    if ( !CheckSaveAndClean() )
        return;

    QString loadFile =
        QFileDialog::getOpenFileName(
            this,
            QString("Open Project..."),
            "",
            QString("Chrono Projects (*.cropj)") );
    if ( loadFile != "" )
    {
        QFile input(loadFile);
        input.open( QIODevice::ReadOnly );
        XmlSerialDocument doc( &input );
        input.close();

        IDeserializer* source = doc.Root().SubElement("project");
        _project = new ChronoProject( source );
        delete source;
        _projectFilename = loadFile;
        _setupView = new ProjectSetupView(_project);
        setCentralWidget(_setupView);
    }
}

void ChronoWindow::SaveProject()
{
    if ( _projectFilename == "" )
    {
        SaveProjectAs();
        return;
    }

    if ( _modifiedFlag )
    {
        QFile output(_projectFilename);
        output.open( QIODevice::WriteOnly );
        XmlSerialDocument doc("chrono-proj");
        doc.Root().Serialize( "project", _project );
        doc.Save( &output );
        output.close();

        _modifiedFlag = false;
    }
}

void ChronoWindow::SaveProjectAs()
{
    QString asFile =
        QFileDialog::getSaveFileName(
            this,
            QString("Save Project..."),
            "",
            QString("Chrono Projects (*.cropj)") );
    if ( asFile != "" )
    {
        _projectFilename = asFile;
        SaveProject();
    }
}

void ChronoWindow::BeginSession()
{
    if ( _session != NULL )
        return;

    _sessionStart = QTime::currentTime();
    _session = _project->CreateSession();
    _sessionView = new SessionView(_session);
    connect( _sessionView, SIGNAL( Finished() ), this, SLOT( EndSession() ) );

    setCentralWidget(_sessionView);
    _setupView = NULL;
}

void ChronoWindow::EndSession()
{
    QFileInfo info(_projectFilename);
    QString defName =
        info.absolutePath() +
        "\\" +
        info.baseName() +
        QDate::currentDate().toString( "_yyyyMMdd" ) +
        _sessionStart.toString("_HHmm") +
        ".crolg";

    QString logFile = "";
    do
    {
        logFile =
            QFileDialog::getSaveFileName(
                this,
                QString("Save Event Log..."),
                defName,
                QString("Chrono Event Logs (*.crolg)") );
        if ( logFile == "" )
        {
            QMessageBox::StandardButton result =
                QMessageBox::warning(
                    this,
                    "Discard Event Log?",
                    "If you proceed, this session will be discarded.\n"
                    "Are you sure you want to discard the event log?",
                    QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::No );
            if ( result == QMessageBox::Yes )
                return;
        }
    } while ( logFile == "" );

    QFile output(logFile);
    output.open( QIODevice::WriteOnly );
    XmlSerialDocument doc("chrono-log");
    doc.Root().Serialize( "session", _session );
    doc.Save( &output );
    output.close();

    _setupView = new ProjectSetupView(_project);
    setCentralWidget(_setupView);
    _sessionView = NULL;
    delete _session;
    _session = NULL;
}

bool ChronoWindow::CheckSaveAndClean()
{
    if ( _session != NULL )
    {
        EndSession();
    }
    if ( _project != NULL )
    {
        if ( _modifiedFlag )
        {
            int answer =
                QMessageBox::question(
                    this,
                    "Current File Modified",
                    "The current project has been modified.\n"
                    "Would you like to save these changes?",
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                    QMessageBox::Yes );
            if ( answer == QMessageBox::Yes )
                SaveProject();
            else if ( answer == QMessageBox::Cancel )
                return false;
        }

        setCentralWidget(NULL);
        _setupView = NULL;
        delete _project;
        _project = NULL;
    }

    return true;
}

void ChronoWindow::closeEvent( QCloseEvent* event )
{
    event->setAccepted( CheckSaveAndClean() );
}

void ChronoWindow::OnModified()
{
    _modifiedFlag = true;
}
