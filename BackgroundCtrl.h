#ifndef BACKGROUNDCTRL_H
#define BACKGROUNDCTRL_H

#include <QDomElement>
#include <QItemSelectionModel>
#include <QObject>
#include <QMap>

#include "QStringMapRefModel.hpp"

class Background;
class QStringList;


class BackgroundCtrl : public QObject
{
    Q_OBJECT

public:
    BackgroundCtrl(const QDomElement& background = QDomElement(), QObject* parent = NULL);
    ~BackgroundCtrl();

    QAbstractItemModel* Model();
    QItemSelectionModel* SelectionModel();

    Background* GetInstance(const QString& title);

    QStringList SharedWith(const BackgroundCtrl& other);

    int  GetMasterVolume();
    bool IsMasterMuted();

    bool Halt(const QStringList& exceptions=QStringList());
    bool Resume();

    void WriteData(QDomElement& background);

public slots:
    bool SetMasterVolume(int vol);
    bool SetMasterMuted(bool mute=true);

    bool AddBackground(const QString& title, const QDomElement& sound = QDomElement());
    bool RemoveBackground(const QString& title);
    void RenameBackground(const QString& title, const QString& newTitle);

signals:
    void Modified();

protected slots:
    void RemoveDeletedBackground();

private:
    int  m_volume;
    bool m_muted;

    //typedef QTriple<Background*, int, bool> BackgroundData;
    typedef QMap<QString, Background*>   BackgroundMap;

    BackgroundMap                   m_bgMap;
    QStringMapRefModel<Background*> m_bgMapModel;
    QItemSelectionModel             m_bgMapSelModel;

};

#endif

