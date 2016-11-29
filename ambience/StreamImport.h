#ifndef STREAMIMPORT_H
#define STREAMIMPORT_H

#include "A_SoundImport.qoh"


class StreamImport : public A_SoundImport
{
public:
    StreamImport(const QString& title, const QString& filename, QObject* parent=NULL);
    virtual ~StreamImport();

protected:
    virtual void Import();

};

#endif
