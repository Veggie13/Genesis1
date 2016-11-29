#include <QDomElement>

#include "ISerializable.h"

#include "XmlSerialElement.h"


XmlSerialElement::XmlSerialElement( QDomDocument doc, const QString& elementName )
:   _element( doc.createElement( elementName ) )
{
}

XmlSerialElement::XmlSerialElement( const QDomElement& element )
:   _element(element)
{
}

QString XmlSerialElement::ChildAttribute(
    const QString& elementName,
    const QString& attrName
) const
{
    QDomElement child = _element.firstChildElement( elementName );
    if ( child.isNull() )
        return "";

    return child.attribute( attrName );
}

void XmlSerialElement::Deserialize( const QString& elementName, int& out ) const
{
    QString attrValue = ChildAttribute( elementName, "intValue" );

    bool ok = false;
    int intValue = attrValue.toInt( &ok );
    if ( ok )
        out = intValue;
}

void XmlSerialElement::Deserialize( const QString& elementName, bool& out ) const
{
    QString attrValue = ChildAttribute( elementName, "boolValue" );

    bool ok = false;
    bool boolValue = (bool)attrValue.toInt( &ok );
    if ( ok )
        out = boolValue;
}

void XmlSerialElement::Deserialize( const QString& elementName, unsigned long long& out ) const
{
    QString attrValue = ChildAttribute( elementName, "ullValue" );

    bool ok = false;
    qulonglong ullValue = attrValue.toULongLong( &ok );
    if ( ok )
        out = (unsigned long long)ullValue;
}

void XmlSerialElement::Deserialize( const QString& elementName, QString& out ) const
{
    QString attrValue = ChildAttribute( elementName, "stringValue" );

    if ( attrValue != "" )
        out = attrValue;
}

void XmlSerialElement::Deserialize( const QString& elementName, QList<IDeserializer*>& out ) const
{
    QDomElement child = _element.firstChildElement( elementName );
    if ( child.isNull() )
        return;

    for ( QDomElement item = child.firstChildElement( "item" );
          !item.isNull();
          item = item.nextSiblingElement( "item" ) )
    {
        out.append( new XmlSerialElement( item ) );
    }
}

IDeserializer* XmlSerialElement::SubElement( const QString& elementName ) const
{
    QDomElement child = _element.firstChildElement( elementName );
    if ( child.isNull() )
        return NULL;

    return new XmlSerialElement( child );
}

void XmlSerialElement::Serialize( const QString& elementName, int in )
{
    QDomElement child = _element.ownerDocument().createElement( elementName );
    child.setAttribute( "intValue", in );
    _element.appendChild( child );
}

void XmlSerialElement::Serialize( const QString& elementName, bool in )
{
    QDomElement child = _element.ownerDocument().createElement( elementName );
    child.setAttribute( "boolValue", (int)in );
    _element.appendChild( child );
}

void XmlSerialElement::Serialize( const QString& elementName, unsigned long long in )
{
    QDomElement child = _element.ownerDocument().createElement( elementName );
    child.setAttribute( "ullValue", (qulonglong)in );
    _element.appendChild( child );
}

void XmlSerialElement::Serialize( const QString& elementName, const QString& in )
{
    QDomElement child = _element.ownerDocument().createElement( elementName );
    child.setAttribute( "stringValue", in );
    _element.appendChild( child );
}

void XmlSerialElement::Serialize( const QString& elementName, const ISerializable* in )
{
    XmlSerialElement serializer( _element.ownerDocument(), elementName );
    in->Serialize( &serializer );
    _element.appendChild( serializer._element );
}

void XmlSerialElement::Serialize( const QString& elementName, const QList<ISerializable*>& in )
{
    QDomElement child = _element.ownerDocument().createElement( elementName );
    for ( QList<ISerializable*>::const_iterator it = in.begin();
          it != in.end();
          it++ )
    {
        XmlSerialElement serializer( child.ownerDocument(), "item" );
        (*it)->Serialize( &serializer );
        child.appendChild( serializer._element );
    }
    _element.appendChild( child );
}
