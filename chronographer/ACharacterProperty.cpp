#include "Defs.h"
#include "IDeserializer.h"
#include "ISerializer.h"

#include "ACharacterProperty.h"


unsigned ACharacterProperty::NEXT_ID = 0;
unsigned ACharacterProperty::TypeId::ID = BasePropertyIdValue;
QMap<unsigned, ACharacterProperty*> ACharacterProperty::s_all;

ACharacterProperty::ACharacterProperty( const QString& name )
:   _id( NEXT_ID++ ),
    _name( name )
{
    s_all[_id] = this;
}

ACharacterProperty::ACharacterProperty( const IDeserializer* source )
{
    ACharacterProperty::Deserialize( source );

    if ( _id >= NEXT_ID )
        NEXT_ID = _id + 1;

    s_all[_id] = this;
}

ACharacterProperty* ACharacterProperty::Get( unsigned id )
{
    if ( !s_all.contains(id) )
        return NULL;

    return s_all[id];
}

void ACharacterProperty::Serialize( ISerializer* dest ) const
{
    dest->Serialize( "propertyTypeId", (int)Type().Value() );
    dest->Serialize( "id", (int)_id );
    dest->Serialize( "name", _name );
}

void ACharacterProperty::Deserialize( const IDeserializer* source )
{
    source->Deserialize( "id", (int&)_id );
    source->Deserialize( "name", _name );
}

QMap<PropertyTypeId, ACharacterProperty::IFactory*>& ACharacterProperty::IFactory::Factories()
{
    static QMap<PropertyTypeId, IFactory*> s_factories;
    return s_factories;
}

void ACharacterProperty::IFactory::RegisterFactory( ACharacterProperty::IFactory* factory )
{
    Factories()[ factory->Type() ] = factory;
}

void ACharacterProperty::IFactory::UnregisterFactory( ACharacterProperty::IFactory* factory )
{
    QMap<PropertyTypeId, IFactory*>::iterator doomedIt = Factories().find( factory->Type() );
    Factories().erase( doomedIt );
}

ACharacterProperty* ACharacterProperty::IFactory::Deserialize( const IDeserializer* source )
{
    int id = -1;
    source->Deserialize( "propertyTypeId", id );

    if ( !Factories().contains( TypeId(id) ) )
        return NULL;

    IFactory* factory = Factories()[TypeId(id)];
    return factory->Create( source );
}

ACharacterProperty* ACharacterProperty::IFactory::Create( TypeId id, const QString& name )
{
    if ( !Factories().contains( id ) )
        return NULL;

    IFactory* factory = Factories()[id];
    return factory->Create( name );
}
