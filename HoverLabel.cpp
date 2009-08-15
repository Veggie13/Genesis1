#include "HoverLabel.qoh"


HoverLabel::HoverLabel(
    const QString& text,
    QWidget* parent,
    Qt::WindowFlags f )
:   QLabel(text, parent, f)
{
    setFrameStyle(QFrame::Box | QFrame::Panel);
}

void HoverLabel::enterEvent(QEvent* event)
{
    emit entered(text());
}

void HoverLabel::leaveEvent(QEvent* event)
{
    emit left(text());
}
