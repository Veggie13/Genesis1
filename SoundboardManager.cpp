#include "QException.h"
#include "Soundboard.qoh"

#include "SoundboardManager.qoh"


SoundboardManager::SoundboardManager(QObject* parent)
:   QObject(parent)
{ }

const QList<Soundboard*>& SoundboardManager::SoundboardList()
{
    return m_sndboards;
}

void SoundboardManager::AddSoundboard(Soundboard* newBoard)
{
    if (newBoard == NULL)
        throw QException("Programming Error: "
                         "Trying to add NULL Soundboard!");

    int index = m_sndboards.lastIndexOf(newBoard);
    if (index != -1)
        throw QException("Programming Error: "
                         "Trying to add a Soundboard that was already present!");

    connect(newBoard, SIGNAL( Modified()  ), this, SIGNAL( Modified()                ));
    connect(newBoard, SIGNAL( destroyed() ), this, SLOT  ( RemoveDeletedSoundboard() ));

    m_sndboards.append(newBoard);
    emit Modified();
}

void SoundboardManager::RemoveSoundboard(Soundboard* board)
{
    int index = m_sndboards.lastIndexOf(board);
    if (index == -1)
        return;

    board->disconnect(this);
    m_sndboards.removeAt(index);
    emit Modified();
}

void SoundboardManager::RemoveDeletedSoundboard()
{
    Soundboard* doomed = reinterpret_cast<Soundboard*>(sender());
    if (doomed == NULL)
        return;

    int index = m_sndboards.lastIndexOf(doomed);
    if (index == -1)
        return;

    m_sndboards.removeAt(index);
    emit Modified();
}
