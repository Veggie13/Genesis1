#include "QException.h"
#include "State.qoh"

#include "Scene.qoh"


Scene::Scene(const QString& title, QObject* parent)
:   QObject(parent),
    m_states(),
    m_title(title)
{
}

Scene::~Scene()
{
    QList<State*>::iterator it;
    for (it = m_states.begin(); it != m_states.end(); it++)
    {
        (*it)->disconnect(this);
        delete (*it);
    }
}

const QString& Scene::Title()
{
    return m_title;
}

void Scene::SetTitle(const QString& title)
{
    m_title = title;
    emit Modified();
}

const QList<State*>& Scene::StateList()
{
    return m_states;
}

void Scene::AddState(State* newState)
{
    if (newState == NULL)
        throw QException("Programming Error: "
                         "Tried to add a NULL State!");

    int index = m_states.lastIndexOf(newState);
    if (-1 != index)
        throw QException("Programming Error: "
                         "Tried to add a State that was already present!");

    connect(newState, SIGNAL( Modified()  ), this, SIGNAL( Modified()           ));
    connect(newState, SIGNAL( destroyed() ), this, SLOT  ( RemoveDeletedState() ));

    m_states.append(newState);
    emit Modified();
}

void Scene::RemoveDeletedState()
{
    State* doomed = reinterpret_cast<State*>(sender());
    if (doomed == NULL)
        return;

    int index = m_states.lastIndexOf(doomed);
    if (-1 == index)
        return;

    int size = m_states.size();
    m_states.removeAt(index);
    size = m_states.size();
    emit Modified();
}
