#include <QVector>

#include "ACharacterProperty.h"
#include "Character.h"
#include "Defs.h"
#include "IDeserializer.h"
#include "ISerializer.h"
#include "Session.h"

#include "ChronoProject.qoh"


ChronoProject::~ChronoProject()
{
    for ( QList<Character*>::iterator it = _characters.begin();
          it != _characters.end();
          it++ )
    {
        delete (*it);
    }
    for ( QList<ACharacterProperty*>::iterator it = _properties.begin();
          it != _properties.end();
          it++ )
    {
        delete (*it);
    }
    for ( QList<CustomEvent::Factory*>::iterator it = _customEventFactories.begin();
          it != _customEventFactories.end();
          it++ )
    {
        delete (*it);
    }
}

QStringList ChronoProject::Characters() const
{
    QStringList result;
    for ( QList<Character*>::const_iterator it = _characters.begin();
          it != _characters.end();
          it++ )
    {
        result.append( (*it)->Name() );
    }

    return result;
}

void ChronoProject::AddCharacter( const QString& name )
{
    _characters.append( new Character( name ) );
    emit Modified();
}

void ChronoProject::RemoveCharacter( const QString& name )
{
    for ( QList<Character*>::iterator it = _characters.begin();
          it != _characters.end();
          it++ )
    {
        if ( (*it)->Name() == name )
        {
            delete (*it);
            _characters.erase( it );
            emit Modified();
            return;
        }
    }
}

void ChronoProject::RenameCharacter( const QString& name, const QString& newName )
{
    for ( QList<Character*>::iterator it = _characters.begin();
          it != _characters.end();
          it++ )
    {
        if ( (*it)->Name() == name )
        {
            (*it)->SetName( newName );
            emit Modified();
            return;
        }
    }
}

QStringList ChronoProject::Properties() const
{
    QStringList result;
    for ( QList<ACharacterProperty*>::const_iterator it = _properties.begin();
          it != _properties.end();
          it++ )
    {
        result.append( (*it)->Name() );
    }

    return result;
}

QMap<ChronoProject::PropertyType, PropertyTypeId> InitPropertyMap()
{
    QMap<ChronoProject::PropertyType, PropertyTypeId> map;
    map[ChronoProject::Value] = PropertyTypeId(IntPropertyIdValue);
    return map;
}

const QMap<ChronoProject::PropertyType, PropertyTypeId>& PropertyMap()
{
    static const QMap<ChronoProject::PropertyType, PropertyTypeId> s_map = InitPropertyMap();
    return s_map;
}

void ChronoProject::AddProperty( ChronoProject::PropertyType type, const QString& name )
{
    ACharacterProperty* property =
        ACharacterProperty::IFactory::Create( PropertyMap()[type], name );

    if ( property != NULL )
    {
        _properties.append( property );
        emit Modified();
    }
}

void ChronoProject::RemoveProperty( const QString& name )
{
    for ( QList<ACharacterProperty*>::iterator it = _properties.begin();
          it != _properties.end();
          it++ )
    {
        if ( (*it)->Name() == name )
        {
            delete (*it);
            _properties.erase( it );
            emit Modified();
            return;
        }
    }
}

QStringList ChronoProject::CustomEvents() const
{
    QStringList result;
    for ( QList<CustomEvent::Factory*>::const_iterator it = _customEventFactories.begin();
          it != _customEventFactories.end();
          it++ )
    {
        result.append( (*it)->Name() );
    }

    return result;
}

void ChronoProject::AddCustomEvent( const QString& name )
{
    _customEventFactories.append( new CustomEvent::Factory( name ) );
    emit Modified();
}

void ChronoProject::RemoveCustomEvent( const QString& name )
{
    for ( QList<CustomEvent::Factory*>::iterator it = _customEventFactories.begin();
          it != _customEventFactories.end();
          it++ )
    {
        if ( (*it)->Name() == name )
        {
            delete (*it);
            _customEventFactories.erase( it );
            emit Modified();
            return;
        }
    }
}

Session* ChronoProject::CreateSession() const
{
    return new Session( _characters, _properties, _customEventFactories );
}

void ChronoProject::Serialize( ISerializer* dest ) const
{
    QVector<ISerializable*> charVec( _characters.count() );
    qCopy( _characters.begin(), _characters.end(), charVec.begin() );
    dest->Serialize( "characters", charVec.toList() );

    QVector<ISerializable*> propVec( _properties.count() );
    qCopy( _properties.begin(), _properties.end(), propVec.begin() );
    dest->Serialize( "properties", propVec.toList() );

    QVector<ISerializable*> eventVec( _customEventFactories.count() );
    qCopy( _customEventFactories.begin(), _customEventFactories.end(), eventVec.begin() );
    dest->Serialize( "customEvents", eventVec.toList() );
}

void ChronoProject::Deserialize( const IDeserializer* source )
{
    QList<IDeserializer*> charList, propList, eventList;
    source->Deserialize( "characters", charList );
    source->Deserialize( "properties", propList );
    source->Deserialize( "customEvents", eventList );

    for ( QList<IDeserializer*>::iterator it = charList.begin();
          it != charList.end();
          it++ )
    {
        _characters.append( new Character( *it ) );
        delete (*it);
    }
    for ( QList<IDeserializer*>::iterator it = propList.begin();
          it != propList.end();
          it++ )
    {
        _properties.append( ACharacterProperty::IFactory::Deserialize( *it ) );
        delete (*it);
    }
    for ( QList<IDeserializer*>::iterator it = eventList.begin();
          it != eventList.end();
          it++ )
    {
        _customEventFactories.append( new CustomEvent::Factory( *it ) );
        delete (*it);
    }
}
