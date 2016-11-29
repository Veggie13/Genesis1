#pragma once

#include <QMap>
#include <QPair>
#include <QStringList>

#include "CustomEvent.h"

#include "ISerializable.h"


class ACharacterPropertyInstance;
class ASessionEvent;

class Session : public ISerializable
{
public:
    Session(
        const QList<Character*>& charList,
        const QList<ACharacterProperty*>& propList,
        const QList<CustomEvent::Factory*>& eventList );
    Session( const IDeserializer* source );
    ~Session();

    void PostEvent( ASessionEvent* event );

    void Start();
    void Stop();
    void TogglePause();
    void MakeNote( const QString& note );

    QStringList Characters() const;
    QStringList Properties() const;
    const QList<CustomEvent::Factory*>& CustomEvents() const
        { return _customEventFactories; }

    Character* CharacterByName(const QString& name) const;

    ACharacterPropertyInstance* Instance(
        const QString& charName,
        const QString& propName ) const;

    virtual void Serialize( ISerializer* dest ) const;

protected:
    virtual void Deserialize( const IDeserializer* source );

private:
    QList< ASessionEvent* > _eventList;

    QList< Character* > _characters;
    QList< ACharacterProperty* > _properties;
    QList< CustomEvent::Factory* > _customEventFactories;

    QMap< QPair<QString,QString>, ACharacterPropertyInstance* > _instances;

};
