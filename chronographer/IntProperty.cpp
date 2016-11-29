#include "Defs.h"
#include "IntPropertyInstance.h"

#include "IntProperty.h"


DEFINE_STANDARD_PROPERTY_FACTORY( IntProperty )

IntProperty::IntProperty( const IDeserializer* source )
:   ACharacterProperty( source )
{
}

ACharacterPropertyInstance*
IntProperty::Instantiate( Session* session, Character* pCharacter )
{
    return new IntPropertyInstance( this, session, pCharacter );
}
