#include <QPair>

#include "InstantSound.h"
#include "SoundMaster.h"

#include "Soundboard.h"


Soundboard::Soundboard(const QDomElement& sndboard, QObject* parent)
:   QObject(parent),
    m_rowCount(16),
    m_colCount(8),
    m_volume(100)
{
    if (sndboard.isNull())
        return;

    QString vol = sndboard.attribute("vol", "0");
    QString rows = sndboard.attribute("rows", "1");
    QString cols = sndboard.attribute("cols", "1");

    SetVolume(vol.toInt());
    Resize(rows.toInt(), cols.toInt());
    for( QDomNode n = sndboard.firstChild();
         !n.isNull();
         n = n.nextSibling() )
    {
        QDomElement effect = n.toElement();
        if ( effect.isNull() || effect.tagName() != "effect" )
            continue;

        QString effectTitle = effect.attribute("title", "");
        QString effectRow = effect.attribute("row", "-1");
        QString effectCol = effect.attribute("col", "-1");

        AddEntry(effectRow.toInt(), effectCol.toInt(), effectTitle);
    }
}

Soundboard::~Soundboard()
{
    for ( SoundGrid::iterator it = m_soundGrid.begin();
          it != m_soundGrid.end();
          it++ )
    {
        it.value().second->disconnect(this);
        SoundMaster::Get().ReturnInstant(it.value().second);
    }
}

int Soundboard::GetRowCount()
{
    return m_rowCount;
}

int Soundboard::GetColCount()
{
    return m_colCount;
}

int Soundboard::GetVolume()
{
    return m_volume;
}

InstantSound* Soundboard::GetEntry(int row, int col)
{
    SoundGrid::iterator finder = m_soundGrid.find( GridCoord(row,col) );
    if (finder == m_soundGrid.end())
        return NULL;

    return finder.value().second;
}

QString Soundboard::GetTitle(int row, int col)
{
    SoundGrid::iterator finder = m_soundGrid.find( GridCoord(row,col) );
    if (finder == m_soundGrid.end())
        return "";

    return finder.value().first;
}

void Soundboard::WriteData(QDomElement& sndboard)
{
    QDomDocument doc = sndboard.ownerDocument();

    sndboard.setAttribute("vol", QString("%1").arg( m_volume ) );
    sndboard.setAttribute("rows", QString("%1").arg( m_rowCount ) );
    sndboard.setAttribute("cols", QString("%1").arg( m_colCount ) );
    for ( SoundGrid::iterator effectIt = m_soundGrid.begin();
          effectIt != m_soundGrid.end();
          effectIt++ )
    {
        QString effectTitle = effectIt.value().first;
        QDomElement effect = doc.createElement("effect");
        effect.setAttribute("row", QString("%1").arg(effectIt.key().first) );
        effect.setAttribute("col", QString("%1").arg(effectIt.key().second) );
        effect.setAttribute("title", effectTitle);
        sndboard.appendChild(effect);
    }
}

bool Soundboard::SetVolume(int vol)
{
    if (vol < 0 || vol > 100)
        return false;

    m_volume = vol;
    emit Modified();
    return true;
}

bool Soundboard::AddEntry(int row, int col, const QString& title)
{
    if (row < 0 || row >= m_rowCount || col < 0 || col >= m_colCount)
        return false;

    SoundGrid::iterator finder = m_soundGrid.find( GridCoord(row,col) );
    if (finder != m_soundGrid.end())
        return false;

    InstantSound* newSound = SoundMaster::Get().CreateInstant(title);
    if (!newSound)
        return false;

    connect(newSound, SIGNAL( destroyed() ), this, SLOT( RemoveDeletedEntries() ));

    m_soundGrid[GridCoord(row,col)] = NamedSound(title, newSound);
    emit Modified();
    return true;
}

void Soundboard::RemoveEntry(int row, int col)
{
    if (row < 0 || row >= m_rowCount || col < 0 || col >= m_colCount)
        return;

    SoundGrid::iterator finder = m_soundGrid.find( GridCoord(row,col) );
    if (finder != m_soundGrid.end())
        SoundMaster::Get().ReturnInstant(finder.value().second);
}

void Soundboard::RemoveEntries(const QString& title)
{
    for ( SoundGrid::iterator it = m_soundGrid.begin();
          it != m_soundGrid.end();
          it++ )
    {
        if (it.value().first == title)
            SoundMaster::Get().ReturnInstant(it.value().second);
    }
}

bool Soundboard::Resize(int rows, int cols)
{
    if (rows < 0 || cols < 0)
        return false;

    if (rows < m_rowCount || cols < m_colCount)
    {
        for ( SoundGrid::iterator it = m_soundGrid.begin();
              it != m_soundGrid.end();
              it++ )
        {
            if (it.key().first >= rows || it.key().second >= cols)
                SoundMaster::Get().ReturnInstant(it.value().second);
        }
    }

    m_rowCount = rows;
    m_colCount = cols;
    emit Modified();
    return true;
}

void Soundboard::RemoveDeletedEntries()
{
    InstantSound* doomed = reinterpret_cast<InstantSound*>(sender());
    if (!doomed)
        return;

    for ( SoundGrid::iterator it = m_soundGrid.begin();
          it != m_soundGrid.end();
          it++ )
    {
        if (it.value().second == doomed)
        {
            emit EntryDeleted(it.key().first, it.key().second);
            it = m_soundGrid.erase(it)--;
        }
    }

    emit Modified();
}
