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

private:
    BASS::Channel* m_channel;

};

#endif
