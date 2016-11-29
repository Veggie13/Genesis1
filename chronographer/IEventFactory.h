#pragma once


class IEventFactory
{
public:
    IEventFactory() { }
    virtual ~IEventFactory() { }

    virtual ASessionEvent* Create( const IDeserializer* source ) const = 0;
};
