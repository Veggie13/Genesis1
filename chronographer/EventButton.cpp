#include "EventButton.qoh"


EventButton::EventButton( CustomEvent::Factory* factory, QWidget* parent )
:   QPushButton(parent),
    _factory(factory)
{
    setText( _factory->Name() );
}

void EventButton::OnClick()
{
    emit Clicked(_factory);
}
