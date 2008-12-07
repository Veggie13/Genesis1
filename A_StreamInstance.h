#ifndef A_STREAMINSTANCE_H
#define A_STREAMINSTANCE_H

#include <QObject>

namespace BASS
{
    class Channel;
}


class A_StreamInstance : public QObject
{
    Q_OBJECT

public:
    A_StreamInstance(BASS::Channel* chan, QObject* parent=NULL)
    : QObject(parent), m_channel(chan) { }
    virtual ~A_StreamInstance() { }

    bool operator ==(const A_StreamInstance& other)
    { return m_channel == other.m_channel; }

protected:
    friend class SoundMaster;

    void Reassign(BASS::Channel* newChan)
    { m_channel = newChan; }

    BASS::Channel* m_channel;

};

#endif
