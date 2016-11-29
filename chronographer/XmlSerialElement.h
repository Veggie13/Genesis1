#pragma once

#include <QDomDocument>
#include <QDomElement>

#include "IDeserializer.h"
#include "ISerializer.h"


class XmlSerialElement :
    public IDeserializer,
    public ISerializer
{
public:
    XmlSerialElement( QDomDocument doc, const QString& elementName );
    XmlSerialElement( const QDomElement& element );

    virtual void Deserialize( const QString& elementName, int& out ) const;
    virtual void Deserialize( const QString& elementName, bool& out ) const;
    virtual void Deserialize( const QString& elementName, unsigned long long& out ) const;
    virtual void Deserialize( const QString& elementName, QString& out ) const;
    virtual void Deserialize( const QString& elementName, QList<IDeserializer*>& out ) const;
    virtual IDeserializer* SubElement( const QString& elementName ) const;

    virtual void Serialize( const QString& elementName, int in );
    virtual void Serialize( const QString& elementName, bool in );
    virtual void Serialize( const QString& elementName, unsigned long long in );
    virtual void Serialize( const QString& elementName, const QString& in );
    virtual void Serialize( const QString& elementName, const ISerializable* in );
    virtual void Serialize( const QString& elementName, const QList<ISerializable*>& in );

private:
    QString ChildAttribute( const QString& elementName, const QString& attrName ) const;

    QDomElement _element;

};
