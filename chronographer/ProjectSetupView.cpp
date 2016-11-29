#include <QItemSelectionModel>
#include <QMessageBox>
#include <QStringListModel>

#include "ChronoProject.qoh"

#include "ProjectSetupView.qoh"


ProjectSetupView::ProjectSetupView( ChronoProject* project, QWidget* parent )
:   QWidget(parent),
    _project(project)
{
    setupUi(this);

    _cboPropTypes->addItem( "Number" );

    connect( _btnAddChar,   SIGNAL( clicked() ), this, SLOT( AddCharacter() ) );
    connect( _btnCharRemove,SIGNAL( clicked() ), this, SLOT( RemoveCharacter() ) );
    connect( _btnCharEdit,  SIGNAL( clicked() ), this, SLOT( EditCharacter() ) );

    connect( _btnAddProp,   SIGNAL( clicked() ), this, SLOT( AddProperty() ) );
    connect( _btnPropRemove,SIGNAL( clicked() ), this, SLOT( RemoveProperty() ) );
    connect( _btnPropEdit,  SIGNAL( clicked() ), this, SLOT( EditProperty() ) );

    connect( _btnAddEvent,      SIGNAL( clicked() ), this, SLOT( AddCustomEvent() ) );
    connect( _btnEventRemove,   SIGNAL( clicked() ), this, SLOT( RemoveCustomEvent() ) );
    connect( _btnEventEdit,     SIGNAL( clicked() ), this, SLOT( EditCustomEvent() ) );

    connect( _edtCharName,  SIGNAL( textChanged(const QString&) ), this, SLOT( UpdateCharacterAddState() ) );
    connect( _edtPropName,  SIGNAL( textChanged(const QString&) ), this, SLOT( UpdatePropertyAddState() ) );
    connect( _edtEventName, SIGNAL( textChanged(const QString&) ), this, SLOT( UpdateCustomEventAddState() ) );

    connect( _lvwCharacters->selectionModel(),
             SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
             this, SLOT( UpdateCharacterSelectionState(const QItemSelection&, const QItemSelection&) ) );
    connect( _lvwProperties->selectionModel(),
             SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
             this, SLOT( UpdatePropertySelectionState(const QItemSelection&, const QItemSelection&) ) );
    connect( _lvwEvents->selectionModel(),
             SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
             this, SLOT( UpdateCustomEventSelectionState(const QItemSelection&, const QItemSelection&) ) );

    _lvwCharacters->addItems( _project->Characters() );
    _lvwProperties->addItems( _project->Properties() );
    _lvwEvents->addItems( _project->CustomEvents() );

    QItemSelection s; // dummy
    UpdateCharacterAddState();
    UpdateCharacterSelectionState(s,s);
    UpdatePropertyAddState();
    UpdatePropertySelectionState(s,s);
    UpdateCustomEventAddState();
    UpdateCustomEventSelectionState(s,s);
}

void ProjectSetupView::AddCharacter()
{
    _project->AddCharacter( _edtCharName->text() );
    _lvwCharacters->addItem( _edtCharName->text() );
    _edtCharName->clear();
}

void ProjectSetupView::RemoveCharacter()
{
    int answer =
        QMessageBox::warning(
            this,
            "Remove Character",
            "Are you sure you want to remove this character from the project?",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No );
    if ( answer == QMessageBox::No )
        return;

    QModelIndexList selection = _lvwCharacters->selectionModel()->selectedIndexes();
    _project->RemoveCharacter( selection.at(0).data().toString() );
    _lvwCharacters->clear();
    _lvwCharacters->addItems( _project->Characters() );
}

void ProjectSetupView::EditCharacter()
{
    QModelIndexList selection = _lvwCharacters->selectionModel()->selectedIndexes();
    _project->RenameCharacter( selection.at(0).data().toString(), _edtCharName->text() );
    _lvwCharacters->clear();
    _lvwCharacters->addItems( _project->Characters() );
}

void ProjectSetupView::UpdateCharacterAddState()
{
    QModelIndexList selection = _lvwCharacters->selectionModel()->selectedIndexes();
    bool isSelection = ( selection.size() > 0 );
    _btnCharEdit->setEnabled( _edtCharName->text() != "" && isSelection );
    _btnAddChar->setEnabled( _edtCharName->text() != "" );
}

void ProjectSetupView::UpdateCharacterSelectionState(const QItemSelection&, const QItemSelection&)
{
    QModelIndexList selection = _lvwCharacters->selectionModel()->selectedIndexes();
    bool isSelection = ( selection.size() > 0 );
    _btnCharEdit->setEnabled( isSelection && _edtCharName->text() != "" );
    _btnCharRemove->setEnabled(isSelection);
}

void ProjectSetupView::AddProperty()
{
    ChronoProject::PropertyType type;
    switch ( _cboPropTypes->currentIndex() )
    {
        case 0: type = ChronoProject::Value; break;
        default: return;
    }
    _project->AddProperty( type, _edtPropName->text() );
    _lvwProperties->addItem( _edtPropName->text() );
    _edtPropName->clear();
}

void ProjectSetupView::RemoveProperty()
{
    int answer =
        QMessageBox::warning(
            this,
            "Remove Property",
            "Are you sure you want to remove this property from the project?",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No );
    if ( answer == QMessageBox::No )
        return;

    QModelIndexList selection = _lvwProperties->selectionModel()->selectedIndexes();
    _project->RemoveProperty( selection.at(0).data().toString() );
    _lvwProperties->clear();
    _lvwProperties->addItems( _project->Properties() );
}

void ProjectSetupView::EditProperty()
{
    QModelIndexList selection = _lvwProperties->selectionModel()->selectedIndexes();
    _project->RemoveProperty( selection.at(0).data().toString() );
    ChronoProject::PropertyType type;
    switch ( _cboPropTypes->currentIndex() )
    {
        case 0: type = ChronoProject::Value; break;
        default: return;
    }
    _project->AddProperty( type, _edtPropName->text() );
    _lvwProperties->clear();
    _lvwProperties->addItems( _project->Properties() );
}

void ProjectSetupView::UpdatePropertyAddState()
{
    QModelIndexList selection = _lvwProperties->selectionModel()->selectedIndexes();
    bool isSelection = ( selection.size() > 0 );
    _btnPropEdit->setEnabled( isSelection && _edtPropName->text() != "" );
    _btnAddProp->setEnabled( _edtPropName->text() != "" );
    _cboPropTypes->setEnabled( _edtPropName->text() != "" );
}

void ProjectSetupView::UpdatePropertySelectionState(const QItemSelection&, const QItemSelection&)
{
    QModelIndexList selection = _lvwProperties->selectionModel()->selectedIndexes();
    bool isSelection = ( selection.size() > 0 );
    _btnPropEdit->setEnabled( isSelection && _edtPropName->text() != "" );
    _btnPropRemove->setEnabled(isSelection);
}

void ProjectSetupView::AddCustomEvent()
{
    _project->AddCustomEvent( _edtEventName->text() );
    _lvwEvents->addItem( _edtEventName->text() );
    _edtEventName->clear();
}

void ProjectSetupView::RemoveCustomEvent()
{
    int answer =
        QMessageBox::warning(
            this,
            "Remove Custom Event",
            "Are you sure you want to remove this event type from the project?",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No );
    if ( answer == QMessageBox::No )
        return;

    QModelIndexList selection = _lvwEvents->selectionModel()->selectedIndexes();
    _project->RemoveCustomEvent( selection.at(0).data().toString() );
    _lvwEvents->clear();
    _lvwEvents->addItems( _project->CustomEvents() );
}

void ProjectSetupView::EditCustomEvent()
{
    QModelIndexList selection = _lvwEvents->selectionModel()->selectedIndexes();
    _project->RemoveCustomEvent( selection.at(0).data().toString() );
    _project->AddCustomEvent( _edtEventName->text() );
    _lvwEvents->clear();
    _lvwEvents->addItems( _project->CustomEvents() );
}

void ProjectSetupView::UpdateCustomEventAddState()
{
    QModelIndexList selection = _lvwEvents->selectionModel()->selectedIndexes();
    bool isSelection = ( selection.size() > 0 );
    _btnEventEdit->setEnabled( isSelection && _edtEventName->text() != "" );
    _btnAddEvent->setEnabled( _edtEventName->text() != "" );
}

void ProjectSetupView::UpdateCustomEventSelectionState(const QItemSelection&, const QItemSelection&)
{
    QModelIndexList selection = _lvwEvents->selectionModel()->selectedIndexes();
    bool isSelection = ( selection.size() > 0 );
    _btnEventEdit->setEnabled( isSelection && _edtEventName->text() != "" );
    _btnEventRemove->setEnabled(isSelection);
}
