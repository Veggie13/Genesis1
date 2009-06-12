#include <QString>

#include "Scene.qoh"
#include "State.qoh"


Scene::Scene(const QDomElement& scene, QObject* parent)
:   QObject(parent),
    m_states(),
    m_stateModel(&m_states)
{
    if (scene.isNull())
        return;

    for( QDomNode n = scene.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement state = n.toElement();
        if ( state.isNull() || state.tagName() != "state")
            continue;

        QString stateTitle = state.attribute("title", "");
        AddState(stateTitle, state);
    }
}

Scene::~Scene()
{
    StateMap::iterator it;
    for (it = m_states.begin(); it != m_states.end(); it++)
    {
        delete it.value();
    }
}

QAbstractItemModel* Scene::Model()
{
    return &m_stateModel;
}

bool Scene::AddState(const QString& stateName, const QDomElement& state)
{
    StateMap::const_iterator it = m_states.constFind(stateName);
    if (it != m_states.constEnd())
        return false;

    State* newState = new State(state);
    if (!newState)
        return false;

    connect(newState, SIGNAL( Modified() ), this, SIGNAL( Modified() ));

    m_states[stateName] = newState;
    emit Modified();
    return true;
}

void Scene::RemoveState(const QString& stateName)
{
    StateMap::iterator it = m_states.find(stateName);
    if (it == m_states.end())
        return;

    State* doomed = (*it);
    delete doomed;

    m_states.erase(it);
    emit Modified();
}

State* Scene::GetState(const QString& stateName)
{
    StateMap::iterator it = m_states.find(stateName);
    if (it == m_states.end())
        return NULL;

    return (*it);
}

void Scene::WriteData(QDomElement& scene)
{
    QDomDocument doc = scene.ownerDocument();

    for ( StateMap::iterator stateIt = m_states.begin();
          stateIt != m_states.end();
          stateIt++ )
    {
        QDomElement state = doc.createElement("state");
        state.setAttribute("title", stateIt.key());
        stateIt.value()->WriteData(state);
        scene.appendChild(state);
    }
}

void Scene::RenameStreamObjects(const QString& title, const QString& newTitle)
{
    StateMap::iterator it;
    for (it = m_states.begin(); it != m_states.end(); it++)
    {
        it.value()->RenameStreamObjects(title, newTitle);
    }
}

void Scene::RenameSampleObjects(const QString& title, const QString& newTitle)
{
    StateMap::iterator it;
    for (it = m_states.begin(); it != m_states.end(); it++)
    {
        it.value()->RenameSampleObjects(title, newTitle);
    }
}
