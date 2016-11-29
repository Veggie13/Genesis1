#ifndef SAMPLEIMPORT_H
#define SAMPLEIMPORT_H

#include "A_SoundImport.qoh"


namespace BASS { class Sample; }
class QByteArray;

class SampleImport : public A_SoundImport
{
public:
    SampleImport(const QString& title, const QString& filename, QObject* parent=NULL);
    virtual ~SampleImport();

protected:
    virtual void Import();

private:
    BASS::Sample* m_sample;
    QByteArray* m_array;

};

#endif
