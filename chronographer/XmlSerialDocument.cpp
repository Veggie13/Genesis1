#include <QIODevice>

#include "XmlSerialElement.h"

#include "XmlSerialDocument.h"


XmlSerialDocument::XmlSerialDocument( const QString& name )
:   _doc(name),
    _root(NULL)
{
    _doc.appendChild( _doc.createElement("root") );
    _root = new XmlSerialElement( _doc.documentElement() );
}

XmlSerialDocument::XmlSerialDocument( QIODevice* dev )
{
    _doc.setContent( dev );
    _root = new XmlSerialElement( _doc.documentElement() );
}

XmlSerialDocument::~XmlSerialDocument()
{
    delete _root;
}

void XmlSerialDocument::Save( QIODevice* dev ) const
{
    dev->write( _doc.toString().toAscii() );
}

XmlSerialElement& XmlSerialDocument::Root()
{
    return *_root;
}
