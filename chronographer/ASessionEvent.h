#pragma once

#include <QMap>
#include <QString>

#include "ISerializable.h"

#include "Defs.h"


class Character;
class ACharacterProperty;

class ASessionEvent : public ISerializable
{
public:
    ASessionEvent(
        const Character* source,
        const Character* target,
        const ACharacterProperty* property
    );
    virtual ~ASessionEvent() { }

    class TypeId
    {
    public:
        TypeId(): _id(ID++) { }
        TypeId(unsigned id): _id(id) { }
        TypeId(const TypeId& other): _id(other._id) { }
        TypeId& operator = (const TypeId& other)
        {
            if ( this != &other ) _id = other._id;
            return *this;
        }

        unsigned Value() const { return _id; }

        bool operator == (const TypeId& other) const
            { return ( _id == other._id ); }
        bool operator < (const TypeId& other) const
            { return ( _id < other._id ); }

    private:
        unsigned _id;
        static unsigned ID;
    };

    class IFactory
    {
    public:
        static ASessionEvent* Deserialize( const IDeserializer* source );

        IFactory() { }
        virtual ~IFactory() { }

        virtual TypeId Type() const = 0;
        virtual ASessionEvent* Create( const IDeserializer* source ) const = 0;

    protected:
        static void RegisterFactory(TypeId id, IFactory* factory);

    private:
        static QMap<TypeId, IFactory*>& Factories();
    };

    const Character* SourceCharacter() const;
    const Character* TargetCharacter() const;
    const ACharacterProperty* PropertyType() const;
    SESSION_TIME TimeStamp() const;

    virtual TypeId Type() const = 0;
    virtual int IntData() const = 0;
    virtual bool BoolData() const = 0;
    virtual QString StringData() const = 0;

    virtual void Serialize( ISerializer* dest ) const;

protected:
    ASessionEvent( const IDeserializer* source );
    virtual void Deserialize( const IDeserializer* source );

private:
    const Character* _source;
    const Character* _target;
    const ACharacterProperty* _property;
    SESSION_TIME _timeStamp;

};
typedef ASessionEvent::TypeId EventTypeId;

#define DECLARE_STANDARD_EVENT_FACTORY(Class_Name) \
    static const EventTypeId ID;                                            \
    class Factory : public ASessionEvent::IFactory { public:                \
        Factory() { RegisterFactory(ID, this); }                            \
        virtual EventTypeId Type() const { return ID; }                     \
        virtual ASessionEvent* Create( const IDeserializer* source ) const  \
            { return new Class_Name( source ); }                            \
        private: static Factory s_inst; };

#define DEFINE_STANDARD_EVENT_FACTORY(Class_Name) \
    const EventTypeId Class_Name::ID( Class_Name##IdValue );    \
    Class_Name::Factory Class_Name::Factory::s_inst;
