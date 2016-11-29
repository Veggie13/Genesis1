#pragma once

#include "ACharacterProperty.h"


class ACharacterPropertyInstance;

class IntProperty : public ACharacterProperty
{
public:
    DECLARE_STANDARD_PROPERTY_FACTORY( IntProperty )

    IntProperty( const QString& name ): ACharacterProperty(name) { }
    IntProperty( const IDeserializer* source );

    virtual PropertyTypeId Type() const { return ID; }

    virtual ACharacterPropertyInstance* Instantiate( Session* session, Character* character );

};
