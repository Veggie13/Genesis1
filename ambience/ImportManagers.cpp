#include "SampleImport.h"
#include "StreamImport.h"

#include "ImportManagers.h"


A_SoundImport* StreamImportManager::InternalImport(
    const QString& title,
    const QString& filename )
{
    return new StreamImport(title, filename);
}

A_SoundImport* SampleImportManager::InternalImport(
    const QString& title,
    const QString& filename )
{
    return new SampleImport(title, filename);
}
