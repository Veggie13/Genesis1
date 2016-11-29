#include <QFocusEvent>
#include <QKeyEvent>

#include "IntPropertyInstance.h"

#include "IntPropertyView.qoh"


IntPropertyView::IntPropertyView( QWidget* parent, IntPropertyInstance* pAssoc )
:   ACharacterPropertyView(parent),
    _pAssoc(pAssoc)
{
    setupUi(this);

    _edtDelta->installEventFilter(this);
    _edtValue->installEventFilter(this);

    connect( _btnPlus, SIGNAL( clicked() ), this, SLOT( PlusManipulate() ) );
    connect( _btnMinus, SIGNAL( clicked() ), this, SLOT( MinusManipulate() ) );
}

void IntPropertyView::InitData()
{
    class IntReader : public IntPropertyInstance::IManipulator
    {
    public:
        Character* _source;
        int _value;
        virtual Character* Source() { return _source; }
        virtual void Manipulate( int& value ) { _value = value; }
    } reader;
    reader._source = _source;

    _pAssoc->Manipulate(&reader);
    _edtValue->setText( QString("%1").arg( reader._value ) );
    _edtDelta->setText( "0" );
}

QString IntPropertyView::Display() const
{
    return _pAssoc->Display();
}

void IntPropertyView::PlusManipulate()
{
    class IntAdder : public IntPropertyInstance::IManipulator
    {
    public:
        Character* _source;
        int _value;
        virtual Character* Source() { return NULL; }
        virtual void Manipulate( int& value ) { value += _value; }
    } adder;
    adder._source = _source;

    adder._value = _edtDelta->text().toInt();
    _pAssoc->Manipulate(&adder);
    emit dataSubmitted( _pAssoc->Display() );
}

void IntPropertyView::MinusManipulate()
{
    class IntSubber : public IntPropertyInstance::IManipulator
    {
    public:
        Character* _source;
        int _value;
        virtual Character* Source() { return NULL; }
        virtual void Manipulate( int& value ) { value -= _value; }
    } subber;
    subber._source = _source;

    subber._value = _edtDelta->text().toInt();
    _pAssoc->Manipulate(&subber);
    emit dataSubmitted( _pAssoc->Display() );
}

void IntPropertyView::ValueManipulate()
{
    class IntSetter : public IntPropertyInstance::IManipulator
    {
    public:
        Character* _source;
        int _value;
        virtual Character* Source() { return NULL; }
        virtual void Manipulate( int& value ) { value = _value; }
    } setter;
    setter._source = _source;

    setter._value = _edtValue->text().toInt();
    _pAssoc->Manipulate(&setter);
    emit dataSubmitted( _pAssoc->Display() );
}

bool IntPropertyView::eventFilter( QObject* watched, QEvent* event )
{
    if ( event->type() == QEvent::KeyPress )
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if ( watched == _edtDelta )
        {
            if ( keyEvent->key() == Qt::Key_Plus )
            {
                PlusManipulate();
                return true;
            }
            if ( keyEvent->key() == Qt::Key_Minus )
            {
                MinusManipulate();
                return true;
            }
            if ( keyEvent->key() == Qt::Key_Enter ||
                 keyEvent->key() == Qt::Key_Return )
            {
                _edtDelta->selectAll();
                return true;
            }
        }
        if ( watched == _edtValue )
        {
            if ( keyEvent->key() == Qt::Key_Enter ||
                 keyEvent->key() == Qt::Key_Return )
            {
                ValueManipulate();
                return true;
            }
        }
    }

    return ACharacterPropertyView::eventFilter(watched, event);
}

void IntPropertyView::focusInEvent( QFocusEvent* event )
{
    _edtDelta->selectAll();
    _edtDelta->setFocus( event->reason() );
}
