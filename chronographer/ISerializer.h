#pragma once

#include <QList>
#include <QString>


class ISerializable;

class ISerializer
{
public:
    ISerializer() { }
    virtual ~ISerializer() { }

    virtual void Serialize( const QString& elementName, int in ) = 0;
    virtual void Serialize( const QString& elementName, bool in ) = 0;
    virtual void Serialize( const QString& elementName, unsigned long long in ) = 0;
    virtual void Serialize( const QString& elementName, const QString& in ) = 0;
    virtual void Serialize( const QString& elementName, const ISerializable* in ) = 0;
    virtual void Serialize( const QString& elementName, const QList<ISerializable*>& in ) = 0;
};
