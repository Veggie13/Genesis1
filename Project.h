#ifndef PROJECT_H
#define PROJECT_H

#include <QDomElement>
#include <QMap>
#include <QObject>
#include <QString>

#include "QStringMapRefModel.hpp"

class Scene;


class Project : public QObject
{
    Q_OBJECT

public:
    Project(const QDomElement& project = QDomElement(), QObject* parent = NULL);
    ~Project();

    QAbstractItemModel* Model();

    bool AddScene(const QString& sceneName, const QDomElement& scene = QDomElement());
    void RemoveScene(const QString& sceneName);

    Scene* GetScene(const QString& sceneName);

    void WriteData(QDomElement& project);

    void RenameStreamObjects(const QString& title, const QString& newTitle);
    void RenameSampleObjects(const QString& title, const QString& newTitle);

signals:
    void Modified();

private:
    typedef QMap<QString, Scene*> SceneMap;
    SceneMap                    m_scenes;
    QStringMapRefModel<Scene*>  m_sceneModel;

};

#endif
