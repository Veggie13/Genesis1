#pragma once

#include <QWidget>


class PanningViewWidget : public QWidget
{
public:
    PanningViewWidget( QWidget* parent = NULL );

    void SetViewContents( QWidget* view );

    virtual bool eventFilter( QObject* obj, QEvent* event );

protected:
    virtual void leaveEvent( QEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void resizeEvent( QResizeEvent* event );
    virtual void showEvent( QShowEvent* event );

private:
    void UpdateParams();
    void MoveView( const QPoint& pos );
    void CenterView();

    QWidget* _view;
    double _xFactor;
    double _yFactor;
    int _xCenter;
    int _yCenter;
};
