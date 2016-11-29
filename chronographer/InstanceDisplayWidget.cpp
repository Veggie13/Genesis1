#include "ACharacterPropertyInstance.h"

#include "InstanceDisplayWidget.qoh"


InstanceDisplayWidget::InstanceDisplayWidget(
    ACharacterPropertyInstance* inst,
    QWidget* parent
)
:   QLabel(parent),
    _inst(inst)
{
    setAlignment( Qt::AlignCenter );
    setText( _inst->Display() );
}
