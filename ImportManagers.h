#ifndef IMPORTMANAGERS_H
#define IMPORTMANAGERS_H

#include "A_ImportManager.qoh"


class StreamImportManager : public A_ImportManager
{
protected:
    virtual A_SoundImport* InternalImport(
        const QString& title,
        const QString& filename );
};

class SampleImportManager : public A_ImportManager
{
protected:
    virtual A_SoundImport* InternalImport(
        const QString& title,
        const QString& filename );
};

#endif
