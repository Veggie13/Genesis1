#include <QMouseEvent>

#include "CharacterLabel.qoh"


CharacterLabel::CharacterLabel( const QString& name, QWidget* parent )
:   DraggableLabel(parent)
{
    setText(name);
    setAlignment(Qt::AlignCenter);
    setFrameStyle(QFrame::Panel);
    setFrameShadow(QFrame::Raised);
}

void CharacterLabel::Click()
{
    emit Clicked();
}

void CharacterLabel::SetDepressed( bool depress )
{
    setFrameShadow( depress ? QFrame::Sunken : QFrame::Raised );
}

void CharacterLabel::mouseReleaseEvent( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
        emit Clicked();
}

void CharacterLabel::mouseDoubleClickEvent( QMouseEvent* event )
{
    if ( event->button() == Qt::RightButton )
        emit DoubleRightClicked();
}
