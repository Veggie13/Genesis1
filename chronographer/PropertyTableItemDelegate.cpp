#include <QKeyEvent>
#include <QModelIndex>

#include "ACharacterPropertyInstance.h"
#include "ACharacterPropertyView.qoh"
#include "Session.h"

#include "PropertyTableItemDelegate.qoh"


PropertyTableItemDelegate::PropertyTableItemDelegate(Session* session)
:   _session(session)
{ }

void PropertyTableItemDelegate::SetNextSource(const QString& name)
{
    _nextSource = name;
}

QWidget* PropertyTableItemDelegate::createEditor(
    QWidget* parent,
    const QStyleOptionViewItem& option,
    const QModelIndex& index
) const
{
    QString colHeader =
        index.model()->headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();
    QString rowHeader =
        index.model()->headerData(index.row(), Qt::Vertical, Qt::DisplayRole).toString();

    ACharacterPropertyInstance* inst = _session->Instance(rowHeader, colHeader);

    ACharacterPropertyView* view = inst->CreateView(parent);
    if ( _nextSource != "" )
    {
        view->SetSource( _session->CharacterByName(_nextSource) );
        _nextSource = "";
    }
    connect( view, SIGNAL( dataSubmitted(const QString&) ), this, SLOT( editorDataSubmitted() ) );

    return view;
}

void PropertyTableItemDelegate::setEditorData(
    QWidget* editor,
    const QModelIndex& index
) const
{
    ACharacterPropertyView* view =
        static_cast<ACharacterPropertyView*>( editor );
    view->InitData();
}

void PropertyTableItemDelegate::setModelData(
    QWidget* editor,
    QAbstractItemModel* model,
    const QModelIndex& index
) const
{
    ACharacterPropertyView* view =
        static_cast<ACharacterPropertyView*>( editor );
    model->setData(index, view->Display(), Qt::DisplayRole);
}

bool PropertyTableItemDelegate::eventFilter( QObject* watched, QEvent* event )
{
    if ( event->type() == QEvent::KeyPress )
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>( event );
        if ( keyEvent->key() == Qt::Key_Enter ||
             keyEvent->key() == Qt::Key_Return ||
             keyEvent->key() == Qt::Key_Tab ||
             keyEvent->key() == Qt::Key_Backtab )
            return false;
    }

    return QItemDelegate::eventFilter(watched, event);
}

void PropertyTableItemDelegate::editorDataSubmitted()
{
    emit commitData( static_cast<QWidget*>( sender() ) );
    emit closeEditor( static_cast<QWidget*>( sender() ) );
}
