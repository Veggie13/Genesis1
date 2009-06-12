#include "Scene.qoh"
#include "Project.qoh"


Project::Project(const QDomElement& project, QObject* parent)
:   QObject(parent),
    m_scenes(),
    m_sceneModel(&m_scenes)
{
    if (project.isNull())
        return;

    for( QDomNode n = project.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement scene = n.toElement();
        if ( scene.isNull() || scene.tagName() != "scene")
            continue;

        QString sceneTitle = scene.attribute("title", "");
        AddScene(sceneTitle, scene);
    }
}

Project::~Project()
{
    SceneMap::iterator it;
    for (it = m_scenes.begin(); it != m_scenes.end(); it++)
    {
        delete (*it);
    }
}

QAbstractItemModel* Project::Model()
{
    return &m_sceneModel;
}

bool Project::AddScene(const QString& sceneName, const QDomElement& scene)
{
    SceneMap::const_iterator it = m_scenes.constFind(sceneName);
    if (it != m_scenes.constEnd())
        return false;

    Scene* newScene = new Scene(scene);
    if (!newScene)
        return false;

    connect(newScene, SIGNAL( Modified() ), this, SIGNAL( Modified() ));

    m_scenes[sceneName] = newScene;
    m_sceneModel.setStringMap(&m_scenes);
    emit Modified();
    return true;
}

void Project::RemoveScene(const QString& sceneName)
{
    SceneMap::iterator it = m_scenes.find(sceneName);
    if (it == m_scenes.end())
        return;

    Scene* doomed = (*it);
    delete doomed;

    m_scenes.erase(it);
    m_sceneModel.setStringMap(&m_scenes);
    emit Modified();
}

Scene* Project::GetScene(const QString& sceneName)
{
    SceneMap::iterator it = m_scenes.find(sceneName);
    if (it == m_scenes.end())
        return NULL;

    return (*it);
}

void Project::WriteData(QDomElement& project)
{
    QDomDocument doc = project.ownerDocument();

    for ( SceneMap::iterator sceneIt = m_scenes.begin();
          sceneIt != m_scenes.end();
          sceneIt++ )
    {
        QDomElement scene = doc.createElement("scene");
        scene.setAttribute("title", sceneIt.key());
        sceneIt.value()->WriteData(scene);
        project.appendChild(scene);
    }
}

void Project::RenameStreamObjects(const QString& title, const QString& newTitle)
{
    SceneMap::iterator it;
    for (it = m_scenes.begin(); it != m_scenes.end(); it++)
    {
        (*it)->RenameStreamObjects(title, newTitle);
    }
}

void Project::RenameSampleObjects(const QString& title, const QString& newTitle)
{
    SceneMap::iterator it;
    for (it = m_scenes.begin(); it != m_scenes.end(); it++)
    {
        (*it)->RenameSampleObjects(title, newTitle);
    }
}
