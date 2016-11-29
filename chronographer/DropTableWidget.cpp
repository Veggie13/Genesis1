#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>

#include "ACharacterPropertyInstance.h"
#include "InstanceDisplayWidget.qoh"
#include "PropertyTableItemDelegate.qoh"
#include "Session.h"

#include "DropTableWidget.qoh"


DropTableWidget::DropTableWidget( QWidget* parent )
:   QTableWidget(parent)
{ }

void DropTableWidget::SetSession( Session* session )
{
    setItemDelegate( new PropertyTableItemDelegate(session) );

    QStringList charNames = session->Characters();
    QStringList propNames = session->Properties();
    setRowCount( charNames.size() );
    setColumnCount( propNames.size() );
    setHorizontalHeaderLabels( propNames );
    setVerticalHeaderLabels( charNames );

    for ( int row = 0; row < charNames.size(); row++ )
    for ( int col = 0; col < propNames.size(); col++ )
    {
        ACharacterPropertyInstance* inst = session->Instance(charNames.at(row), propNames.at(col));
        model()->setData( model()->index(row,col), inst->Display(), Qt::DisplayRole );
        model()->setData( model()->index(row,col), Qt::AlignCenter, Qt::TextAlignmentRole );
    }
}

void DropTableWidget::dragEnterEvent( QDragEnterEvent* evt )
{
    if ( evt->mimeData()->hasText() )
        evt->acceptProposedAction();
}

void DropTableWidget::dragMoveEvent( QDragMoveEvent* evt )
{
    int row = rowAt( evt->pos().y() );
    int col = columnAt( evt->pos().x() );
    if ( row >= 0 && row < rowCount() &&
         col >= 0 && col < columnCount() )
    {
        evt->acceptProposedAction();
    }
}

void DropTableWidget::dropEvent( QDropEvent* evt )
{
    int row = rowAt( evt->pos().y() );
    int col = columnAt( evt->pos().x() );
    if ( row >= 0 && row < rowCount() &&
         col >= 0 && col < columnCount() )
    {
        setCurrentCell( row, col );
        evt->acceptProposedAction();
        QModelIndex index = model()->index( row, col );
        static_cast<PropertyTableItemDelegate*>( itemDelegate() )
            ->SetNextSource( evt->mimeData()->text() );
        edit( index );
    }
}
