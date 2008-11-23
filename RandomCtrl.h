#ifndef RANDOMCTRL_H
#define RANDOMCTRL_H

#include <QDomElement>
#include <QItemSelectionModel>
#include <QObject>
#include <QMap>

#include "QStringMapRefModel.hpp"

class QStringList;
class RandomSound;


class RandomCtrl : public QObject
{
    Q_OBJECT

public:
    RandomCtrl(const QDomElement& random = QDomElement(), QObject* parent = NULL);
    ~RandomCtrl();

    QAbstractItemModel* Model();
    QItemSelectionModel* SelectionModel();

    RandomSound* GetInstance(const QString& title);

    int  GetMasterVolume();
    bool IsMasterMuted();

    void Halt();
    void Resume();

    void WriteData(QDomElement& random);

public slots:
    bool SetMasterVolume(int vol);
    bool SetMasterMuted(bool mute=true);

    bool AddRandom(const QString& title, const QDomElement& effect = QDomElement());
    bool RemoveRandom(const QString& title);

signals:
    void Modified();

protected slots:
    void RemoveDeletedRandom();

private:
    int  m_volume;
    bool m_muted;

    //typedef QPair<RandomSound*, bool> RandomData;
    typedef QMap<QString, RandomSound*> RandomMap;

    RandomMap                           m_randMap;
    QStringMapRefModel<RandomSound*>    m_randMapModel;
    QItemSelectionModel                 m_randMapSelModel;

};

#endif

