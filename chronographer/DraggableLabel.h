#pragma once

#include <QLabel>
#include <QPoint>


class DraggableLabel : public QLabel
{
public:
    DraggableLabel( QWidget* parent = NULL );

protected:
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mousePressEvent( QMouseEvent* event );

private:
    QPoint _dragStartPos;

};
