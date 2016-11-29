#include "IDeserializer.h"
#include "ISerializer.h"

#include "Character.h"


unsigned Character::NEXT_ID = 0;
QMap<unsigned, Character*> Character::s_all;

Character::Character( const QString& name )
:   _name( name ),
    _id( NEXT_ID++ )
{
    s_all[_id] = this;
}

Character::Character( const IDeserializer* source )
{
    Deserialize( source );
    s_all[_id] = this;
}

Character::~Character()
{
    s_all.erase( s_all.find(_id) );
}

Character* Character::Get( unsigned id )
{
    if ( !s_all.contains(id) )
        return NULL;

    return s_all[id];
}

void Character::Serialize( ISerializer* dest ) const
{
    dest->Serialize( "name", _name );
    dest->Serialize( "id", (int)_id );
}

void Character::Deserialize( const IDeserializer* source )
{
    source->Deserialize( "name", _name );
    source->Deserialize( "id", (int&)_id );
    if ( _id >= NEXT_ID )
        NEXT_ID = _id + 1;
}
