#ifndef INSTANTSOUND_H
#define INSTANTSOUND_H

#include <QObject>

namespace BASS
{
    class Channel;
}


class InstantSound : public QObject
{
    Q_OBJECT

public:
    InstantSound(BASS::Channel* chan, QObject* parent=NULL);
    ~InstantSound();

public slots:
    bool Play(int vol);

protected:
    friend class SoundMaster;
    void Reassign(BASS::Channel* newChan);

private:
    BASS::Channel* m_channel;

};

#endif
