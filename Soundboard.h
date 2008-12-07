#ifndef SOUNDBOARD_H
#define SOUNDBOARD_H

#include <QDomElement>
#include <QMap>
#include <QObject>

class InstantSound;
template <typename T1, typename T2> class QPair;


class Soundboard : public QObject
{
    Q_OBJECT

public:
    Soundboard(const QDomElement& sndboard = QDomElement(), QObject* parent = NULL);
    ~Soundboard();

    int GetRowCount();
    int GetColCount();

    int GetVolume();

    InstantSound*   GetEntry(int row, int col);
    QString         GetTitle(int row, int col);

    void WriteData(QDomElement& sndboard);

public slots:
    bool SetVolume(int vol);

    bool AddEntry(int row, int col, const QString& title);

    void RemoveEntry(int row, int col);
    void RemoveEntries(const QString& title);

    void RenameEntries(const QString& title, const QString& newTitle);

    bool Resize(int rows, int cols);

signals:
    void EntryDeleted(int row, int col);
    void Modified();

private slots:
    void RemoveDeletedEntries();

private:
    typedef QPair<int,int>                  GridCoord;
    typedef QPair<QString, InstantSound*>   NamedSound;
    typedef QMap<GridCoord, NamedSound>     SoundGrid;

    SoundGrid m_soundGrid;

    int m_rowCount;
    int m_colCount;

    int m_volume;

};

#endif
