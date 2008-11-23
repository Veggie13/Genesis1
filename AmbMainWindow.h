#ifndef AMBMAINWINDOW_H
#define AMBMAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QStringList>

#include "AmbMainWindowUi.h"

class AmbMainWidget;
class FileSelectionDlg;
class QDomElement;
class QHBoxLayout;
class QSettings;
class Project;
class SceneEditorDlg;


class AmbMainWindow : public QMainWindow, private Ui::AmbMainWindowUi
{
    Q_OBJECT

public:
    AmbMainWindow(int argc, char* argv[], QWidget* parent=NULL);
    virtual ~AmbMainWindow();

protected slots:
    virtual void closeEvent(QCloseEvent* evt);
    virtual void showEvent(QShowEvent* evt);

    void OnStartup();

    void Load();
    void LoadRecent();
    void Save();
    void SaveAs();

    void NewProject();
    void LoadProject(const QString& filename);
    void SaveProject(const QString& filename);

    void SetModified();
    void ClearModified();

    void ImportStreamFile(const QString& title, const QString& filename);
    void ImportSampleFile(const QString& title, const QString& filename);

    void CloseStreamFile(const QString& title);
    void CloseSampleFile(const QString& title);

    void SelectSong();
    void SelectBackground();
    void SelectRandom();
    void SelectInstant(int row, int col);

    void UpdateSceneList();
    void UpdateStateList();
    void SwitchSceneState();

    void ApplyWidgetExpandLeftSetting(bool expand);

    void ShowAboutDlg();

private:
    void AddToRecentProjectList(const QString& filename);
    void PutRecentProjectListOnMenu();
    void LoadAndApplySettings();

    void LoadStreamImportList(const QDomElement& longImports);
    void LoadSampleImportList(const QDomElement& shortImports);

    bool CheckModified();
    void UpdateAppTitle();


    QHBoxLayout*    m_mainWidgetLayout;
    AmbMainWidget*  m_mainWidget;

    Project*    m_project;
    QString     m_projectPath;
    bool        m_modified;

    SceneEditorDlg*     m_sceneEditDlg;
    FileSelectionDlg*   m_longFileDlg;
    FileSelectionDlg*   m_shortFileDlg;

    bool m_starting;

    QSettings*              m_settings;
    QStringList             m_recentFilesList;
    QMap<QAction*, QString> m_recentFilesMap;


    static const unsigned int   VERSION_CODE;
    static const char           APP_NAME[];
    static const char           COMPANY_NAME[];
    static const int            RECENT_FILES_LIST_MAX;
    static QString VersionString();
    static QString ProjectTitle(const QString& filename);

};

#endif
