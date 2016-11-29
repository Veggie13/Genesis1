#include "IntPropertyChangeEvent.h"
#include "IntPropertyView.qoh"
#include "Session.h"

#include "IntPropertyInstance.h"


IntPropertyInstance::IntPropertyInstance(
    IntProperty* property,
    Session* session,
    Character* pOwner,
    int initialValue
)
:   ACharacterPropertyInstance(session, pOwner),
    _property(property),
    _value(initialValue)
{ }

ACharacterPropertyView*
IntPropertyInstance::CreateView( QWidget* parent )
{
    return new IntPropertyView( parent, this );
}

void IntPropertyInstance::Manipulate( IntPropertyInstance::IManipulator* pManip )
{
    int oldValue = _value;
    pManip->Manipulate( _value );
    if ( oldValue != _value )
        SessionContext()->PostEvent(
            new IntPropertyChangeEvent(
                pManip->Source(),
                Owner(),
                _property,
                _value )
            );
}
