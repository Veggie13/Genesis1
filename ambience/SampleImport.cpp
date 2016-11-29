#include <QByteArray>
#include <QFile>

#include <bass_system.h>
#include <bass_channel.h>
#include <bass_sample.h>

#include "QException.h"

#include "SampleImport.h"


SampleImport::SampleImport(
    const QString& title,
    const QString& filename,
    QObject* parent )
:   A_SoundImport(title, filename, parent),
    m_sample(NULL),
    m_array(NULL)
{
    Initialize();
}

SampleImport::~SampleImport()
{
    delete GetChannel();
    SetChannel(NULL);

    delete m_sample;
    delete m_array;
}

void SampleImport::Import()
{
    QFile sampleFile(Filename());
    if (!sampleFile.open(QIODevice::ReadOnly))
        throw QException("Unexpected Import Failure: "
                         "Could not open import file for reading!");


    delete m_array;
    delete m_sample;

    m_array = new QByteArray( sampleFile.readAll() );
    sampleFile.close();

    try
    {
        m_sample =
            BASS::System::Get().LoadSampleFromMemory(
                m_array->data(),
                m_array->length(),
                2,
                BASS_SAMPLE_OVER_POS );
    }
    catch (...)
    {
        delete m_array;
        throw;
    }

    SetChannel(m_sample->GetChannel(false));
}
