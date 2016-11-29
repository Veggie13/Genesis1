#pragma once

#include "ASessionEvent.h"


class CustomEvent : public ASessionEvent
{
public:
    class Factory :
        public ASessionEvent::IFactory,
        public ISerializable
    {
    public:
        Factory( const IDeserializer* source );
        Factory( const QString& eventName )
            : _name(eventName) { RegisterFactory(_type, this); }
        Factory( const Factory& other )
            : _name(other._name), _type(other._type) { }

        CustomEvent* Create() const { return new CustomEvent( _name, _type ); }

        const QString& Name() const { return _name; }
        virtual EventTypeId Type() const { return _type; }
        virtual ASessionEvent* Create( const IDeserializer* source ) const
            { return new CustomEvent( _type, source ); }

        virtual void Serialize( ISerializer* dest ) const;

    protected:
        virtual void Deserialize( const IDeserializer* source );

    private:
        QString _name;
        EventTypeId _type;
    };
    friend class Factory;

    virtual EventTypeId Type() const { return _type; }
    virtual int IntData() const { return 0; }
    virtual bool BoolData() const { return false; }
    virtual QString StringData() const { return _name; }

    virtual void Serialize( ISerializer* dest ) const;

protected:
    virtual void Deserialize( const IDeserializer* source );

private:
    CustomEvent( const EventTypeId& type, const IDeserializer* source )
        : ASessionEvent(source), _type(type) { Deserialize(source); }
    CustomEvent( const QString& eventName, const EventTypeId& type )
        : ASessionEvent(NULL, NULL, NULL), _name(eventName), _type(type) { }

    QString _name;
    EventTypeId _type;

};
