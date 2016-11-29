#pragma once

#include <QMap>
#include <QString>

#include "ISerializable.h"


class Character : public ISerializable
{
public:
    Character( const IDeserializer* source );
    Character( const QString& name );
    virtual ~Character();
    static Character* Get( unsigned id );

    const QString& Name() const { return _name; }
    void SetName( const QString& newName ) { _name = newName; }

    unsigned ID() const { return _id; }

    virtual void Serialize( ISerializer* dest ) const;

protected:
    virtual void Deserialize( const IDeserializer* source );

private:
    QString _name;
    unsigned _id;

    static unsigned NEXT_ID;
    static QMap<unsigned, Character*> s_all;

};
