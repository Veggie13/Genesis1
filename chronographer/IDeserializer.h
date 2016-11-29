#pragma once

#include <QList>
#include <QString>


class IDeserializer
{
public:
    IDeserializer() { }
    virtual ~IDeserializer() { }

    virtual void Deserialize( const QString& elementName, int& out ) const = 0;
    virtual void Deserialize( const QString& elementName, bool& out ) const = 0;
    virtual void Deserialize( const QString& elementName, unsigned long long& out ) const = 0;
    virtual void Deserialize( const QString& elementName, QString& out ) const = 0;
    virtual void Deserialize( const QString& elementName, QList<IDeserializer*>& out ) const = 0;
    virtual IDeserializer* SubElement( const QString& elementName ) const = 0;
};
