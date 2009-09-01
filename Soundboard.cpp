#include <QPair>

#include "QException.h"
#include "SoundboardInstance.h"

#include "Soundboard.qoh"


Soundboard::Soundboard(QObject* parent)
:   QObject(parent),
    m_rowCount(16),
    m_colCount(8),
    m_volume(100)
{
}

Soundboard::~Soundboard()
{
    for ( SoundGrid::iterator it = m_soundGrid.begin();
          it != m_soundGrid.end();
          it++ )
    {
        it.value()->disconnect(this);
        delete it.value();
    }
}

const Soundboard::SoundGrid& Soundboard::GetSoundGrid()
{
    return m_soundGrid;
}

int Soundboard::RowCount()
{
    return m_rowCount;
}

int Soundboard::ColCount()
{
    return m_colCount;
}

int Soundboard::Volume()
{
    return m_volume;
}

SoundboardInstance* Soundboard::Entry(int row, int col)
{
    SoundGrid::iterator finder = m_soundGrid.find( GridCoord(row,col) );
    if (finder == m_soundGrid.end())
        return NULL;

    return finder.value();
}

void Soundboard::SetVolume(int vol)
{
    if (vol < 0 || vol > 100)
        throw QException("Programming Error: "
                         "Tried to set volume outside the valid range!");

    m_volume = vol;
    emit MasterVolumeChanged(m_volume);
    emit Modified();
}

void Soundboard::AddEntry(int row, int col, SoundboardInstance* newSound)
{
    if (row < 0 || row >= m_rowCount || col < 0 || col >= m_colCount)
        throw QException("Programming Error: "
                         "Tried to add sound outside valid dimensions!");

    SoundGrid::iterator finder = m_soundGrid.find( GridCoord(row,col) );
    if (finder != m_soundGrid.end())
        throw QException("Programming Error: "
                         "Tried to add sound to occupied button!");

    if (newSound == NULL)
        throw QException("Programming Error: "
                         "Tried to add NULL sound to Soundboard!");

    connect(newSound, SIGNAL( destroyed() ), this, SLOT( RemoveDeletedEntries() ));

    connect( this,      SIGNAL( MasterVolumeChanged(int) ),
             newSound,  SLOT  ( SetMasterVolume(int)     ) );

    m_soundGrid[GridCoord(row,col)] = newSound;
    newSound->SetMasterVolume(m_volume);
    newSound->Resume();
    emit EntryAdded(row, col, newSound);
    emit Modified();
}

void Soundboard::Resize(int rows, int cols)
{
    if (rows < 0 || cols < 0)
        throw QException("Programming Error: "
                         "Tried to resize to invalid dimensions!");

    if (rows < m_rowCount || cols < m_colCount)
    {
        QList<SoundboardInstance*> doomedList;
        for ( SoundGrid::iterator it = m_soundGrid.begin();
              it != m_soundGrid.end();
              it++ )
        {
            if (it.key().first >= rows || it.key().second >= cols)
                doomedList.append(it.value());
        }
        for ( QList<SoundboardInstance*>::const_iterator lIt = doomedList.begin();
              lIt != doomedList.end();
              lIt++ )
        {
            delete (*lIt);
        }
    }

    m_rowCount = rows;
    m_colCount = cols;
    emit Modified();
}

void Soundboard::RemoveDeletedEntries()
{
    SoundboardInstance* doomed = reinterpret_cast<SoundboardInstance*>(sender());
    if (doomed == NULL)
        return;

    for ( SoundGrid::iterator it = m_soundGrid.begin();
          it != m_soundGrid.end();
          it++ )
    {
        if (it.value() == doomed)
        {
            emit EntryDeleted(it.key().first, it.key().second);
            m_soundGrid.erase(it);
        }
    }

    emit Modified();
}
