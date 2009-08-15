#include "Project.qoh"
#include "Scene.qoh"

#include "SceneState.qoh"


SceneState::SceneState(QWidget* parent)
:   QLabel(parent),
    m_project(NULL)
{
    setupUi(this);
    setBackgroundRole(QPalette::Window);
    setFrameStyle(QFrame::WinPanel);
    setAutoFillBackground(true);
    setEnabled(false);

    connect( m_switchBtn,   SIGNAL( clicked()                           ),
             this,          SLOT  ( OnSwitchSelected()                  ) );
    connect( m_sceneCbo,    SIGNAL( currentIndexChanged(const QString&) ),
             this,          SLOT  ( OnSceneChanged(const QString&)      ) );
}

void SceneState::Associate(Project* proj)
{
    if (m_project == proj)
        return;

    m_project = proj;
    if (!proj)
    {
        setEnabled(false);
        return;
    }

    setEnabled(true);
    m_sceneCbo->setModel(proj->Model());
}

void SceneState::OnSwitchSelected()
{
    emit SceneStateSwitched(m_sceneCbo->currentText(), m_stateCbo->currentText());
}

void SceneState::OnSceneChanged(const QString& sceneName)
{
    if (!m_project)
        return;

    Scene* curScene = m_project->GetScene(sceneName);
    if (curScene)
        m_stateCbo->setModel(curScene->Model());
}
