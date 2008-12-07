#ifndef MUSICCTRL_H
#define MUSICCTRL_H

#include <QDomElement>
#include <QItemSelectionModel>
#include <QObject>
#include <QMap>

#include "QStringMapRefModel.hpp"

class Song;


class MusicCtrl : public QObject
{
    Q_OBJECT

public:
    MusicCtrl(const QDomElement& music = QDomElement(), QObject* parent = NULL);
    ~MusicCtrl();

    QAbstractItemModel* Model();
    QItemSelectionModel* SelectionModel();

    bool SharesCurrentSongWith(const MusicCtrl& other);
    QString CurrentSong();

    int  GetVolume();
    bool IsMuted();

    bool Halt(bool keepCurrent=false);
    void Resume(bool useSpecific=false, const QString& title=QString());

    void WriteData(QDomElement& music);

signals:
    void Modified();
    void SongSelected(const QString& title);

public slots:
    bool SetVolume(int vol);
    bool SetMuted(bool mute=true);
    bool SetSong(const QString& title);

    bool AddSong(const QString& title);
    bool RemoveSong(const QString& title);
    void RenameSong(const QString& title, const QString& newTitle);

    void SelectRandomSong();

protected slots:
    void RemoveDeletedSong();

private:
    int  m_volume;
    bool m_muted;

    typedef QMap<QString, Song*> SongMap;

    SongMap                     m_songMap;
    QStringMapRefModel<Song*>   m_songMapModel;
    QItemSelectionModel         m_songMapSelModel;
    SongMap::iterator           m_curSong;

};

#endif
