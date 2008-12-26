#include <QTimer>

#include "AmbSplash.h"


AmbSplash::AmbSplash()
:   QDialog(NULL, Qt::CustomizeWindowHint)
{
    setupUi(this);
}

AmbSplash::~AmbSplash()
{ }

void AmbSplash::showEvent(QShowEvent* evt)
{
    QTimer::singleShot(2000, this, SLOT( accept() ));
}
