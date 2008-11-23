#ifndef AMBSPLASH_H
#define AMBSPLASH_H

#include <QDialog>

#include "AmbSplashUi.h"


class AmbSplash : public QDialog, private Ui::AmbSplashUi
{
    Q_OBJECT

public:
    AmbSplash();
    ~AmbSplash();

protected slots:
    virtual void showEvent(QShowEvent* evt);

};

#endif
