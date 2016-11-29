#include <ctime>

#include "ACharacterProperty.h"
#include "Character.h"
#include "Defs.h"
#include "IDeserializer.h"
#include "ISerializer.h"

#include "ASessionEvent.h"


unsigned ASessionEvent::TypeId::ID = BaseEventIdValue;

ASessionEvent::ASessionEvent(
    const Character* source,
    const Character* target,
    const ACharacterProperty* property
)
:   _source(source),
    _target(target),
    _property(property)
{
    clock_t currTime = clock();
    _timeStamp = (SESSION_TIME)currTime;
}

ASessionEvent::ASessionEvent( const IDeserializer* source )
{
    ASessionEvent::Deserialize( source );
}

const Character* ASessionEvent::SourceCharacter() const
{
    return _source;
}

const Character* ASessionEvent::TargetCharacter() const
{
    return _target;
}

const ACharacterProperty* ASessionEvent::PropertyType() const
{
    return _property;
}

SESSION_TIME ASessionEvent::TimeStamp() const
{
    return _timeStamp;
}

void ASessionEvent::Serialize( ISerializer* dest ) const
{
    if ( _source ) dest->Serialize( "source", (int)_source->ID() );
    if ( _target ) dest->Serialize( "target", (int)_target->ID() );
    if ( _property ) dest->Serialize( "property", (int)_property->ID() );
    dest->Serialize( "timeStamp", _timeStamp );
    dest->Serialize( "eventId", (int)Type().Value() );
}

void ASessionEvent::Deserialize( const IDeserializer* source )
{
    int sourceId = -1, targetId = -1, propertyId = -1;
    source->Deserialize( "source", sourceId );
    source->Deserialize( "target", targetId );
    source->Deserialize( "property", propertyId );
    source->Deserialize( "timeStamp", _timeStamp );

    _source = Character::Get( sourceId );
    _target = Character::Get( targetId );
    _property = ACharacterProperty::Get( propertyId );
}

QMap<EventTypeId, ASessionEvent::IFactory*>& ASessionEvent::IFactory::Factories()
{
    static QMap<EventTypeId, IFactory*> s_factories;
    return s_factories;
}

void ASessionEvent::IFactory::RegisterFactory( EventTypeId id, ASessionEvent::IFactory* factory )
{
    Factories()[id] = factory;
}

ASessionEvent* ASessionEvent::IFactory::Deserialize( const IDeserializer* source )
{
    int id = -1;
    source->Deserialize( "eventId", id );

    if ( !Factories().contains( TypeId(id) ) )
        return NULL;

    IFactory* factory = Factories()[TypeId(id)];
    return factory->Create( source );
}
