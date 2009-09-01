#include <bass_system.h>
#include <bass_stream.h>

#include "StreamImport.h"


StreamImport::StreamImport(
    const QString& title,
    const QString& filename,
    QObject* parent )
:   A_SoundImport(title, filename, parent)
{
    Initialize();
}

StreamImport::~StreamImport()
{
}

void StreamImport::Import()
{
    BASS::Stream* newStream =
        BASS::System::Get().LoadStreamFromFile(Filename().toAscii().data(),0,0,0);

    SetChannel(newStream);
}
