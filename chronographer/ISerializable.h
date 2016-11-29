#pragma once


class IDeserializer;
class ISerializer;

class ISerializable
{
public:
    ISerializable() { }
    virtual ~ISerializable() { }

    virtual void Serialize( ISerializer* dest ) const = 0;

protected:
    virtual void Deserialize( const IDeserializer* source ) = 0;

};
