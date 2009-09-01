#include "ImportManagers.h"
#include "QException.h"
#include "Scene.qoh"

#include "Project.qoh"


Project::Project(QObject* parent)
:   QObject(parent),
    m_scenes(),
    m_streamMgr(NULL),
    m_sampleMgr(NULL)
{
    m_streamMgr = new StreamImportManager;
    m_sampleMgr = new SampleImportManager;

    connect(m_streamMgr, SIGNAL( Modified() ), this, SIGNAL( Modified() ));
    connect(m_sampleMgr, SIGNAL( Modified() ), this, SIGNAL( Modified() ));
}

Project::~Project()
{
    QList<Scene*>::iterator it;
    for (it = m_scenes.begin(); it != m_scenes.end(); it++)
    {
        (*it)->disconnect(this);
        delete (*it);
    }

    delete m_streamMgr;
    delete m_sampleMgr;
}

const QList<Scene*>& Project::SceneList()
{
    return m_scenes;
}

A_ImportManager* Project::StreamManager()
{
    return m_streamMgr;
}

A_ImportManager* Project::SampleManager()
{
    return m_sampleMgr;
}

void Project::AddScene(Scene* newScene)
{
    if (newScene == NULL)
        throw QException("Programming Error: "
                         "Tried to add NULL Scene!");

    int index = m_scenes.lastIndexOf(newScene);
    if (-1 != index)
        throw QException("Programming Error: "
                         "Tried to add a Scene that was already present!");

    connect(newScene, SIGNAL( Modified()  ), this, SIGNAL( Modified()           ));
    connect(newScene, SIGNAL( destroyed() ), this, SLOT  ( RemoveDeletedScene() ));

    m_scenes.append(newScene);
    emit Modified();
}

void Project::RemoveDeletedScene()
{
    Scene* doomed = reinterpret_cast<Scene*>(sender());
    if (doomed == NULL)
        return;

    int index = m_scenes.lastIndexOf(doomed);
    if (-1 == index)
        return;

    m_scenes.removeAt(index);
    emit Modified();
}
