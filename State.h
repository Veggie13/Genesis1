#ifndef STATE_H
#define STATE_H

#include <QDomElement>
#include <QObject>

class BackgroundCtrl;
class MusicCtrl;
class RandomCtrl;
class Soundboard;


class State : public QObject
{
    Q_OBJECT

public:
    State(const QDomElement& state = QDomElement(), QObject* parent = NULL);
    ~State();

    MusicCtrl*      GetMusicController();
    BackgroundCtrl* GetBackgroundController();
    RandomCtrl*     GetRandomController();
    Soundboard*     GetSoundboard();

    void WriteData(QDomElement& state);

    void RenameStreamObjects(const QString& title, const QString& newTitle);
    void RenameSampleObjects(const QString& title, const QString& newTitle);

signals:
    void Modified();

private:
    MusicCtrl*      m_music;
    BackgroundCtrl* m_background;
    RandomCtrl*     m_random;
    Soundboard*     m_sndboard;

};

#endif
