#include "Character.h"

#include "CharacterSwitchEvent.h"


DEFINE_STANDARD_EVENT_FACTORY( CharacterSwitchEvent )

CharacterSwitchEvent::CharacterSwitchEvent(
    const Character* from,
    const Character* to )
:   ASessionEvent( from, to, NULL )
{ }

CharacterSwitchEvent::CharacterSwitchEvent( const IDeserializer* source )
:   ASessionEvent( source )
{ }

QString CharacterSwitchEvent::StringData() const
{
    return TargetCharacter()->Name();
}
