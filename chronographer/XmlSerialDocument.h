#pragma once

#include <QDomDocument>


class XmlSerialElement;

class XmlSerialDocument
{
public:
    XmlSerialDocument( const QString& name );
    XmlSerialDocument( QIODevice* dev );
    ~XmlSerialDocument();

    void Save( QIODevice* dev ) const;

    XmlSerialElement& Root();

private:
    QDomDocument _doc;
    XmlSerialElement* _root;

};
