#include <QDialog>
#include <QFrame>
#include <QMessageBox>
#include <QSpinBox>
#include <QVBoxLayout>

#include "CharacterLabel.qoh"
#include "CharacterSwitchEvent.h"
#include "EventButton.qoh"
#include "InitiativeDlgUi.h"
#include "InitiativeOrderDlg.qoh"
#include "MakeNoteDlgUi.h"
#include "PanningViewWidget.h"
#include "Session.h"

#include "SessionView.qoh"


SessionView::SessionView( Session* session, QWidget* parent )
:   QWidget(parent),
    _firstLayout(true),
    _idealWidth(0),
    _session(session),
    _started(false),
    _curCharacter(NULL)
{
    setupUi(this);

    _bottom->installEventFilter(this);

    _btnStartStop = new QPushButton("Start");

    _btnPause = new QPushButton("Pause");
    _btnPause->setDisabled(true);

    _btnNote = new QPushButton("Note...");
    _btnNote->setDisabled(true);

    _frmEvents = new QFrame();
    QHBoxLayout* layout = new QHBoxLayout();
    _frmEvents->setLayout( layout );
    layout->addItem( new QSpacerItem(1, 1, QSizePolicy::Expanding ) );
    _bottom->SetViewContents( _frmEvents );

    connect( _btnStartStop, SIGNAL( clicked() ), this, SLOT( StartStop() ) );
    connect( _btnPause, SIGNAL( clicked() ), this, SLOT( TogglePause() ) );
    connect( _btnNote, SIGNAL( clicked() ), this, SLOT( MakeNote() ) );

    _propertyTable->SetSession(_session);
}

void SessionView::InsertInitiative(const QString& name, int position)
{
    CharacterLabel* label = new CharacterLabel(name);
    connect( label, SIGNAL( Clicked() ), this, SLOT( SwitchCharacter() ) );
    connect( label, SIGNAL( DoubleRightClicked() ), this, SLOT( DelayAction() ) );

    QVBoxLayout* layout = static_cast<QVBoxLayout*>( _frmInitSequence->layout() );
    layout->insertWidget(position + 1, label);
}

void SessionView::InsertEventButton(CustomEvent::Factory* factory, int position)
{
    EventButton* button = new EventButton(factory);
    connect(button, SIGNAL( Clicked(CustomEvent::Factory*) ),
            this,   SLOT( PostEvent(CustomEvent::Factory*) ) );
    _eventButtons.append(button);

    InsertEventButton(button, position + 3);
}

void SessionView::InsertEventButton(QPushButton* btn, int position)
{
    QHBoxLayout* layout = static_cast<QHBoxLayout*>( _frmEvents->layout() );
    if ( layout->count() > 1 &&
         layout->count() * _btnStartStop->sizeHint().width() > _frmEvents->width() )
    {
        _frmEvents->resize( _frmEvents->width() + _btnStartStop->sizeHint().width(), _frmEvents->height() );
    }

    _idealWidth += btn->sizeHint().width();

    btn->setMouseTracking(true);
    btn->installEventFilter(_bottom);
    layout->insertWidget(position, btn);
    layout->activate();
}

bool SessionView::eventFilter( QObject* obj, QEvent* event )
{
    if ( obj == _bottom && event->type() == QEvent::Resize )
    {
        if ( _bottom->width() > _idealWidth )
            _frmEvents->resize( _bottom->size() );
        else
            _frmEvents->resize( _idealWidth, _bottom->height() );
    }

    return QWidget::eventFilter(obj, event);
}

void SessionView::showEvent( QShowEvent* event )
{
    if ( _firstLayout )
    {
        _frmEvents->resize( _bottom->size() );

        InsertEventButton( _btnStartStop, 0 );
        InsertEventButton( _btnPause, 1 );
        InsertEventButton( _btnNote, 2 );
        const QList<CustomEvent::Factory*>& customEvents = _session->CustomEvents();
        for ( int pos = 0; pos < customEvents.size(); pos++ )
        {
            InsertEventButton( customEvents.at(pos), pos );
            _eventButtons.at(pos)->setDisabled(true);
        }

        _firstLayout = false;
    }
}

void SessionView::StartStop()
{
    if ( _started )
    {
        QMessageBox::StandardButton result =
            QMessageBox::warning(
                this,
                "Stop Session",
                "Are you sure you want to end this session?",
                QMessageBox::Yes|QMessageBox::Cancel,
                QMessageBox::Cancel );
        if ( result == QMessageBox::Yes )
        {
            _session->Stop();
            emit Finished();
        }

        return;
    }

    QStringList characters = _session->Characters();
    QList< QPair<double,QString> > result;
    for ( QStringList::iterator it = characters.begin();
          it != characters.end();
          it++ )
    {
        Ui::InitiativeDlgUi ui;
        QDialog dlg(this);
        ui.setupUi(&dlg);
        ui._lblCharacterName->setText(*it);
        dlg.exec();

        int init = ui._spnInitiative->value();
        result.append( QPair<double,QString>(-init, *it) );
    }
    qStableSort( result );
    QStringList commons;
    QList< QPair<double,QString> >::iterator lastIt = result.begin();
    commons.append( (*lastIt).second );
    for ( QList< QPair<double,QString> >::iterator it = lastIt + 1;
          it != result.end();
          it++ )
    {
        if ( (*it).first != (*lastIt).first )
        {
            if ( commons.size() > 1 )
            {
                InitiativeOrderDlg dlg(commons, this);
                dlg.exec();

                commons = dlg.Order();
                for ( int i = 1; i <= commons.size(); i++ )
                    (*(it - i)).second = *(commons.end() - i);
            }

            commons.clear();
        }

        commons.append( (*it).second );
        lastIt = it;
    }
    if ( commons.size() > 1 )
    {
        InitiativeOrderDlg dlg(commons, this);
        dlg.exec();

        commons = dlg.Order();
        for ( int i = 1; i <= commons.size(); i++ )
            (*(lastIt - i)).second = *(commons.end() - i);
    }
    for ( int position = 0; position < result.size(); position++ )
    {
        InsertInitiative( result.at(position).second, position );
    }

    _btnStartStop->setText( "Stop" );
    _btnPause->setEnabled(true);
    _btnNote->setEnabled(true);
    _propertyTable->setEnabled(true);
    for ( QList<EventButton*>::iterator it = _eventButtons.begin();
          it != _eventButtons.end();
          it++ )
    {
        (*it)->setEnabled(true);
    }

    _started = true;
    _session->Start();
}

void SessionView::TogglePause()
{
    if ( _btnPause->text() == "Pause" )
        _btnPause->setText( "Unpause" );
    else
        _btnPause->setText( "Pause" );

    _session->TogglePause();
}

void SessionView::MakeNote()
{
    QDialog dlg(this);
    Ui::MakeNoteDlgUi ui;
    ui.setupUi(&dlg);

    int result = dlg.exec();
    if ( result == QDialog::Rejected )
        return;

    _session->MakeNote( ui._txtNote->toPlainText() );
}

void SessionView::PostEvent( CustomEvent::Factory* factory )
{
    ASessionEvent* event = factory->Create();
    _session->PostEvent( event );
}

void SessionView::SwitchCharacter()
{
    Character* source = NULL;
    if ( _curCharacter )
    {
        _curCharacter->SetDepressed(false);
        source = _session->CharacterByName( _curCharacter->text() );
    }

    _curCharacter = static_cast<CharacterLabel*>( sender() );
    _curCharacter->SetDepressed(true);
    Character* target = _session->CharacterByName( _curCharacter->text() );
    _session->PostEvent( new CharacterSwitchEvent(source, target) );
}

void SessionView::DelayAction()
{
    CharacterLabel* label = static_cast<CharacterLabel*>( sender() );
    if ( _curCharacter == label )
    {
        _curCharacter->Click();
    }

    label->disconnect(this);
    _frmInitSequence->layout()->removeWidget(label);
    QVBoxLayout* layout = static_cast<QVBoxLayout*>( _frmWaiters->layout() );
    layout->insertWidget(1, label);
    connect( label, SIGNAL( Clicked() ), this, SLOT( RestoreAction() ) );
}

void SessionView::RestoreAction()
{
    CharacterLabel* label = static_cast<CharacterLabel*>( sender() );

    label->disconnect(this);
    _frmWaiters->layout()->removeWidget(label);
    QVBoxLayout* layout = static_cast<QVBoxLayout*>( _frmInitSequence->layout() );
    int position = 0;
    if ( _curCharacter )
        position = layout->indexOf(_curCharacter);
    layout->insertWidget(position + 1, label);
    connect( label, SIGNAL( Clicked() ), this, SLOT( SwitchCharacter() ) );
    connect( label, SIGNAL( DoubleRightClicked() ), this, SLOT( DelayAction() ) );
    label->Click();
}
