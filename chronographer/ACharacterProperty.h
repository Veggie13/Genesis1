#pragma once

#include <QString>
#include <QMap>

#include "ISerializable.h"


class ACharacterPropertyInstance;
class Character;
class ACharacterPropertyView;
class Session;

class ACharacterProperty : public ISerializable
{
public:
    ACharacterProperty( const QString& name );
    virtual ~ACharacterProperty() { }
    static ACharacterProperty* Get( unsigned id );

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
        static ACharacterProperty* Deserialize( const IDeserializer* source );
        static ACharacterProperty* Create( TypeId id, const QString& name );

        IFactory() { }
        virtual ~IFactory() { UnregisterFactory(this); }

        virtual TypeId Type() const = 0;
        virtual ACharacterProperty* Create( const IDeserializer* source ) const = 0;
        virtual ACharacterProperty* Create( const QString& name ) const = 0;

    protected:
        static void RegisterFactory( IFactory* factory );
        static void UnregisterFactory( IFactory* factory );

    private:
        static QMap<TypeId, IFactory*>& Factories();
    };

    unsigned ID() const { return _id; }
    const QString& Name() const { return _name; }
    virtual TypeId Type() const = 0;

    virtual ACharacterPropertyInstance* Instantiate( Session* session, Character* character ) = 0;

    virtual void Serialize( ISerializer* dest ) const;

protected:
    ACharacterProperty( const IDeserializer* source );
    virtual void Deserialize( const IDeserializer* source );

private:
    unsigned _id;
    QString _name;

    static unsigned NEXT_ID;
    static QMap<unsigned, ACharacterProperty*> s_all;

};
typedef ACharacterProperty::TypeId PropertyTypeId;

#define DECLARE_STANDARD_PROPERTY_FACTORY( Class_Name ) \
    static const PropertyTypeId ID;                                             \
    class Factory : public ACharacterProperty::IFactory { public:               \
        Factory() { RegisterFactory(this); }                                    \
        virtual PropertyTypeId Type() const { return ID; }                      \
        virtual ACharacterProperty* Create( const IDeserializer* source ) const \
            { return new Class_Name( source ); }                                \
        virtual ACharacterProperty* Create( const QString& name ) const         \
            { return new Class_Name( name ); }                                  \
    private: static Factory s_inst; };

#define DEFINE_STANDARD_PROPERTY_FACTORY( Class_Name ) \
    const PropertyTypeId Class_Name::ID( Class_Name##IdValue ); \
    Class_Name::Factory Class_Name::Factory::s_inst;
