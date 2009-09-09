#include "Project.qoh"
#include "Scene.qoh"
#include "State.qoh"
#include "TitleCarrierListModel.hpp"

#include "SceneState.qoh"


SceneState::SceneState(QWidget* parent)
:   QLabel(parent),
    m_project(NULL),
    m_sceneListModel(NULL),
    m_stateListModel(NULL),
    m_sceneName(""),
    m_stateName("")
{
    setupUi(this);
    setBackgroundRole(QPalette::Window);
    setFrameStyle(QFrame::WinPanel);
    setAutoFillBackground(true);
    setEnabled(false);

    m_sceneListModel = new TitleCarrierListModel;
    m_sceneCbo->setModel(m_sceneListModel);

    m_stateListModel = new TitleCarrierListModel;
    m_stateCbo->setModel(m_stateListModel);

    connect( m_switchBtn,   SIGNAL( clicked()                           ),
             this,          SLOT  ( OnSwitchSelected()                  ) );
    connect( m_sceneCbo,    SIGNAL( currentIndexChanged(const QString&) ),
             this,          SLOT  ( OnSceneChanged(const QString&)      ) );
}

void SceneState::Associate(Project* proj)
{
    if (m_project == proj)
        return;

    if (m_project)
    {
        m_project->disconnect(this);
        disconnect(m_project);
        m_sceneName = "";
        m_stateName = "";
    }

    m_project = proj;
    if (!proj)
    {
        setEnabled(false);
        m_stateListModel->setList( QList<I_TitleCarrier*>() );
        m_sceneListModel->setList( QList<I_TitleCarrier*>() );
        return;
    }

    setEnabled(true);
    m_sceneListModel->setList(proj->SceneList());

    connect(proj,   SIGNAL( Modified()      ),
            this,   SLOT  ( UpdateLists()   ) );
    connect(proj,   SIGNAL( CurrentStateChanged(State*) ),
            this,   SLOT  ( OnStateChanged(State*)      ) );
    connect(proj,   SIGNAL( destroyed()     ),
            this,   SLOT  ( RemoveProject() ) );

    connect(this,   SIGNAL( StateSwitched(State*)   ),
            proj,   SLOT  ( SetCurrentState(State*) ) );
}

void SceneState::OnSwitchSelected()
{
    State* curState = dynamic_cast<State*>(
        m_stateCbo->itemData(m_stateCbo->currentIndex(), Qt::UserRole)
            .value<I_TitleCarrier*>()
        );

    m_sceneName = curState->ParentScene()->Title();
    m_stateName = curState->Title();
    emit StateSwitched(curState);
}

void SceneState::OnSceneChanged(const QString& sceneName)
{
    if (!m_project)
        return;

    Scene* curScene = dynamic_cast<Scene*>(
        m_sceneCbo->itemData(m_sceneCbo->currentIndex(), Qt::UserRole)
            .value<I_TitleCarrier*>()
        );

    if (curScene)
        m_stateListModel->setList(curScene->StateList());
}

void SceneState::OnStateChanged(State* newCurState)
{
    State* curState = dynamic_cast<State*>(
        m_stateCbo->itemData(m_stateCbo->currentIndex(), Qt::UserRole)
            .value<I_TitleCarrier*>()
        );

    if (curState == newCurState)
        return;

    int newCurSceneIndex = -1;
    if (newCurState)
    {
        newCurSceneIndex =
            m_sceneCbo->findText(newCurState->ParentScene()->Title());
    }
    m_sceneCbo->setCurrentIndex(newCurSceneIndex);

    int newCurStateIndex = -1;
    if (newCurState)
    {
        newCurStateIndex =
            m_stateCbo->findText(newCurState->Title());
    }
    m_stateCbo->setCurrentIndex(newCurStateIndex);
}

void SceneState::UpdateLists()
{
    m_sceneListModel->setList(m_project->SceneList());

    int index = m_sceneCbo->findData(m_sceneName, Qt::DisplayRole);
    if (index < 0)
        m_sceneName = "";
    else
        m_sceneCbo->setCurrentIndex(index);

    Scene* curScene = dynamic_cast<Scene*>(
        m_sceneCbo->itemData(m_sceneCbo->currentIndex(), Qt::UserRole)
            .value<I_TitleCarrier*>()
        );

    if (curScene == NULL)
    {
        m_stateName = "";
        m_stateListModel->setList( QList<I_TitleCarrier*>() );
        return;
    }

    m_stateListModel->setList(curScene->StateList());

    index = m_stateCbo->findData(m_stateName, Qt::DisplayRole);
    if (index < 0)
        m_stateName = "";
    else
        m_stateCbo->setCurrentIndex(index);
}

void SceneState::RemoveProject()
{
    m_project = NULL;
    setEnabled(false);
    m_stateListModel->setList( QList<I_TitleCarrier*>() );
    m_sceneListModel->setList( QList<I_TitleCarrier*>() );
    m_stateName = "";
    m_sceneName = "";
}
