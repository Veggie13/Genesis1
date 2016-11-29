#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

#include "DraggableLabel.h"


DraggableLabel::DraggableLabel( QWidget* parent )
:   QLabel(parent)
{ }

void DraggableLabel::mousePressEvent( QMouseEvent* event )
{
    if (event->button() == Qt::LeftButton)
        _dragStartPos = event->pos();
}

void DraggableLabel::mouseMoveEvent( QMouseEvent* event )
{
    if ( !(event->buttons() & Qt::LeftButton) )
        return;

    if ( (event->pos() - _dragStartPos).manhattanLength()
         < QApplication::startDragDistance() )
        return;

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;

    mimeData->setText( text() );
    drag->setMimeData(mimeData);

    drag->exec();
}
