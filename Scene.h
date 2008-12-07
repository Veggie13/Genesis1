#ifndef SCENE_H
#define SCENE_H

#include <QDomElement>
#include <QMap>
#include <QObject>

#include "QStringMapRefModel.hpp"

class QString;
class State;


class Scene : public QObject
{
    Q_OBJECT

public:
    Scene(const QDomElement& scene = QDomElement(), QObject* parent = NULL);
    ~Scene();

    QAbstractItemModel* Model();

    bool AddState(const QString& stateName, const QDomElement& state = QDomElement());
    void RemoveState(const QString& stateName);

    State* GetState(const QString& stateName);

    void WriteData(QDomElement& scene);

    void RenameStreamObjects(const QString& title, const QString& newTitle);
    void RenameSampleObjects(const QString& title, const QString& newTitle);

signals:
    void Modified();

private:
    typedef QMap<QString, State*> StateMap;
    StateMap                    m_states;
    QStringMapRefModel<State*>  m_stateModel;

};

#endif
