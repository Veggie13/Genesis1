#include "InitiativeOrderDlg.qoh"


InitiativeOrderDlg::InitiativeOrderDlg(
    const QStringList& names,
    QWidget* parent )
:   QDialog(parent)
{
    setupUi(this);

    _lvwNames->addItems( names );

    connect( _btnUp, SIGNAL( clicked() ), this, SLOT( MoveUp() ) );
    connect( _btnDown, SIGNAL( clicked() ), this, SLOT( MoveDown() ) );
}

QStringList InitiativeOrderDlg::Order() const
{
    QStringList names;
    for ( int row = 0; row < _lvwNames->count(); row++ )
    {
        names.append( _lvwNames->item(row)->text() );
    }
    return names;
}

void InitiativeOrderDlg::MoveUp()
{
    QModelIndexList selection = _lvwNames->selectionModel()->selectedIndexes();
    if ( selection.size() < 1 )
        return;

    int row = selection.at(0).row();
    if ( row == 0 )
        return;

    QString name = selection.at(0).data(Qt::DisplayRole).toString();
    _lvwNames->model()->removeRow( selection.at(0).row() );
    _lvwNames->insertItem( row - 1, name );
}

void InitiativeOrderDlg::MoveDown()
{
    QModelIndexList selection = _lvwNames->selectionModel()->selectedIndexes();
    if ( selection.size() < 1 )
        return;

    int row = selection.at(0).row();
    if ( row == _lvwNames->count() - 1 )
        return;

    QString name = selection.at(0).data(Qt::DisplayRole).toString();
    _lvwNames->model()->removeRow( selection.at(0).row() );
    _lvwNames->insertItem( row + 1, name );
}
