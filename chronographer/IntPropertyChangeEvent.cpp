#include "Defs.h"
#include "IDeserializer.h"
#include "ISerializer.h"
#include "IntProperty.h"

#include "IntPropertyChangeEvent.h"


DEFINE_STANDARD_EVENT_FACTORY( IntPropertyChangeEvent )

IntPropertyChangeEvent::IntPropertyChangeEvent(
    Character* source,
    Character* target,
    IntProperty* property,
    int newValue )
:   ASessionEvent(source, target, property), _newValue(newValue)
{ }

IntPropertyChangeEvent::IntPropertyChangeEvent( const IDeserializer* source )
:   ASessionEvent(source)
{
    Deserialize( source );
}

void IntPropertyChangeEvent::Serialize( ISerializer* dest ) const
{
    ASessionEvent::Serialize(dest);
    dest->Serialize( "newValue", _newValue );
}

void IntPropertyChangeEvent::Deserialize( const IDeserializer* source )
{
    source->Deserialize( "newValue", _newValue );
}
