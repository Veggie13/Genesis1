#include "IDeserializer.h"
#include "ISerializer.h"

#include "CustomEvent.h"


void CustomEvent::Serialize( ISerializer* dest ) const
{
    ASessionEvent::Serialize(dest);
    dest->Serialize( "name", _name );
}

void CustomEvent::Deserialize( const IDeserializer* source )
{
    source->Deserialize( "name", _name );
}

CustomEvent::Factory::Factory( const IDeserializer* source )
{
    Deserialize( source );
    RegisterFactory( _type, this );
}

void CustomEvent::Factory::Serialize( ISerializer* dest ) const
{
    dest->Serialize( "typeId", (int)_type.Value() );
    dest->Serialize( "name", _name );
}

void CustomEvent::Factory::Deserialize( const IDeserializer* source )
{
    int id = -1;
    source->Deserialize( "typeId", id );
    _type = EventTypeId(id);

    source->Deserialize( "name", _name );
}
