#pragma once

#include "ASessionEvent.h"


class IntProperty;

class IntPropertyChangeEvent : public ASessionEvent
{
public:
    DECLARE_STANDARD_EVENT_FACTORY( IntPropertyChangeEvent )

    IntPropertyChangeEvent(
        Character* source,
        Character* target,
        IntProperty* property,
        int newValue );
    IntPropertyChangeEvent( const IDeserializer* source );

    virtual EventTypeId Type() const { return ID; }
    virtual int IntData() const { return _newValue; }
    virtual bool BoolData() const { return false; }
    virtual QString StringData() const
        { return QString("%1").arg(_newValue); }

    virtual void Serialize( ISerializer* dest ) const;

protected:
    virtual void Deserialize( const IDeserializer* source );

private:
    int _newValue;

};
