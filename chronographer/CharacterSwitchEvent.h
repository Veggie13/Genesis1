#pragma once

#include "ASessionEvent.h"


class CharacterSwitchEvent : public ASessionEvent
{
public:
    DECLARE_STANDARD_EVENT_FACTORY( CharacterSwitchEvent )

    CharacterSwitchEvent( const Character* from, const Character* to );
    CharacterSwitchEvent( const IDeserializer* source );

    virtual TypeId Type() const { return ID; }
    virtual int IntData() const { return 0; }
    virtual bool BoolData() const { return false; }
    virtual QString StringData() const;

};
