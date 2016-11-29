#pragma once

#include "ACharacterPropertyInstance.h"


class IntProperty;

class IntPropertyInstance : public ACharacterPropertyInstance
{
public:
    IntPropertyInstance(
        IntProperty* property,
        Session* session,
        Character* pOwner,
        int initialValue = 0 );

    virtual ACharacterPropertyView* CreateView( QWidget* parent );
    virtual QString Display() const { return QString("%1").arg(_value); }


    class IManipulator
    {
    public:
        IManipulator() { }
        virtual ~IManipulator() { }

        virtual void Manipulate( int& value ) = 0;
        virtual Character* Source() = 0;
    };
    void Manipulate( IManipulator* pManip );

private:
    IntProperty* _property;
    int _value;

};
