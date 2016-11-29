#include <QVector>
#include <QMessageBox>

#include "ACharacterProperty.h"
#include "BasicEvents.h"
#include "Character.h"
#include "IDeserializer.h"
#include "ISerializer.h"
#include "NoteEvent.h"

#include "Session.h"


Session::Session(
    const QList<Character*>& charList,
    const QList<ACharacterProperty*>& propList,
    const QList<CustomEvent::Factory*>& eventList )
:   _characters( charList ),
    _properties( propList ),
    _customEventFactories( eventList )
{
    for ( QList<Character*>::iterator cIt = _characters.begin();
          cIt != _characters.end();
          cIt++ )
    for ( QList<ACharacterProperty*>::iterator pIt = _properties.begin();
          pIt != _properties.end();
          pIt++ )
    {
        QPair<QString,QString> index( (*cIt)->Name(), (*pIt)->Name() );
        _instances[index] = (*pIt)->Instantiate( this, *cIt );
    }
}

Session::Session( const IDeserializer* source )
{
    Deserialize( source );
}

Session::~Session()
{
    for ( QList< ASessionEvent* >::iterator it = _eventList.begin();
          it != _eventList.end();
          it++ )
    {
        delete (*it);
    }
}

void Session::PostEvent( ASessionEvent* event )
{
    _eventList.append( event );
}

void Session::Start()
{
    _eventList.append( new StartEvent() );
}

void Session::Stop()
{
    _eventList.append( new EndEvent() );
}

void Session::TogglePause()
{
    _eventList.append( new PauseToggleEvent() );
}

void Session::MakeNote( const QString& note )
{
    _eventList.append( new NoteEvent(note) );
}

QStringList Session::Characters() const
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

QStringList Session::Properties() const
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

Character* Session::CharacterByName(const QString& name) const
{
    for ( QList<Character*>::const_iterator it = _characters.begin();
          it != _characters.end();
          it++ )
    {
        if ( (*it)->Name() == name )
            return (*it);
    }
    return NULL;
}

ACharacterPropertyInstance*
Session::Instance( const QString& charName, const QString& propName ) const
{
    return _instances.value( QPair<QString,QString>( charName, propName ), NULL );
}

void Session::Serialize( ISerializer* dest ) const
{
    QVector<ISerializable*> eventVec( _eventList.count() );
    qCopy( _eventList.begin(), _eventList.end(), eventVec.begin() );
    dest->Serialize( "eventList", eventVec.toList() );

    QVector<ISerializable*> charVec( _characters.count() );
    qCopy( _characters.begin(), _characters.end(), charVec.begin() );
    dest->Serialize( "characters", charVec.toList() );

    QVector<ISerializable*> propVec(_properties.count() );
    qCopy( _properties.begin(), _properties.end(), propVec.begin() );
    dest->Serialize( "properties", propVec.toList() );

    QVector<ISerializable*> customVec( _customEventFactories.count() );
    qCopy( _customEventFactories.begin(), _customEventFactories.end(), customVec.begin() );
    dest->Serialize( "customEvents", customVec.toList() );
}

void Session::Deserialize( const IDeserializer* source )
{
    QList<IDeserializer*> deserialList;
    source->Deserialize( "characters", deserialList );
    for ( QList<IDeserializer*>::iterator it = deserialList.begin();
          it != deserialList.end();
          it++ )
    {
        Character* character = new Character( *it );
        _characters.append( character );
        delete (*it);
    }

    deserialList.clear();
    source->Deserialize( "properties", deserialList );
    for ( QList<IDeserializer*>::iterator it = deserialList.begin();
          it != deserialList.end();
          it++ )
    {
        ACharacterProperty* property = ACharacterProperty::IFactory::Deserialize( *it );
        _properties.append( property );
        delete (*it);
    }

    deserialList.clear();
    source->Deserialize( "customEvents", deserialList );
    for ( QList<IDeserializer*>::iterator it = deserialList.begin();
          it != deserialList.end();
          it++ )
    {
        CustomEvent::Factory* factory = new CustomEvent::Factory( *it );
        _customEventFactories.append( factory );
        delete (*it);
    }

    deserialList.clear();
    source->Deserialize( "eventList", deserialList );
    for ( QList<IDeserializer*>::iterator it = deserialList.begin();
          it != deserialList.end();
          it++ )
    {
        ASessionEvent* event = ASessionEvent::IFactory::Deserialize( *it );
        _eventList.append( event );
        delete (*it);
    }
}
