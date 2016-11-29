#include <QMouseEvent>

#include "PanningViewWidget.h"


PanningViewWidget::PanningViewWidget( QWidget* parent )
:   QWidget(parent),
    _view( NULL ),
    _xFactor( 0 ),
    _yFactor( 0 ),
    _xCenter( 0 ),
    _yCenter( 0 )
{
    setMouseTracking(true);
}

void PanningViewWidget::SetViewContents( QWidget* view )
{
    if ( _view != NULL )
        delete _view;
    _view = view;
    if ( _view == NULL )
        return;

    _view->setParent(this);
    _view->setMouseTracking(true);
    _view->installEventFilter(this);

    CenterView();
}

bool PanningViewWidget::eventFilter( QObject* obj, QEvent* event )
{
    if ( event->type() == QEvent::MouseMove )
    {
        return this->event(event);
    }
    else if ( obj == _view && event->type() == QEvent::Resize )
    {
        UpdateParams();
        CenterView();
    }

    return false;
}

void PanningViewWidget::leaveEvent( QEvent* event )
{
    if ( _view == NULL )
        return;

    CenterView();
}

void PanningViewWidget::mouseMoveEvent( QMouseEvent* event )
{
    if ( _view == NULL )
        return;

    MoveView( mapFromGlobal( event->globalPos() ) );
}

void PanningViewWidget::resizeEvent( QResizeEvent* event )
{
    if ( _view == NULL )
        return;

    UpdateParams();
    CenterView();
}

void PanningViewWidget::showEvent( QShowEvent* event )
{
    if ( _view == NULL )
        return;

    UpdateParams();
    CenterView();
}

void PanningViewWidget::UpdateParams()
{
    _xCenter = width() / 2;
    _yCenter = height() / 2;

    _xFactor = ( width() - _view->width() ) / (double)width();
    _yFactor = ( height() - _view->height() ) / (double)height();
}

void PanningViewWidget::MoveView( const QPoint& pos )
{
    _view->move( (int)(pos.x() * _xFactor), (int)(pos.y() * _yFactor) );
}

void PanningViewWidget::CenterView()
{
    if ( geometry().contains( QCursor::pos() ) )
        MoveView( mapFromGlobal( QCursor::pos() ) );
    else
        MoveView( QPoint( _xCenter, _yCenter ) );
}
