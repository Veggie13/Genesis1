/********************************************************************************
** Form generated from reading ui file 'InitiativeOrderDlgUi.ui'
**
** Created: Thu Sep 16 21:31:01 2010
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef INITIATIVEORDERDLGUI_H
#define INITIATIVEORDERDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class Ui_InitiativeOrderDlgUi
{
public:
    QHBoxLayout *hboxLayout;
    QListWidget *_lvwNames;
    QVBoxLayout *vboxLayout;
    QPushButton *_btnUp;
    QPushButton *_btnDown;
    QSpacerItem *spacerItem;
    QPushButton *_btnDone;

    void setupUi(QDialog *InitiativeOrderDlgUi)
    {
    if (InitiativeOrderDlgUi->objectName().isEmpty())
        InitiativeOrderDlgUi->setObjectName(QString::fromUtf8("InitiativeOrderDlgUi"));
    QSize size(247, 216);
    size = size.expandedTo(InitiativeOrderDlgUi->minimumSizeHint());
    InitiativeOrderDlgUi->resize(size);
    hboxLayout = new QHBoxLayout(InitiativeOrderDlgUi);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    _lvwNames = new QListWidget(InitiativeOrderDlgUi);
    _lvwNames->setObjectName(QString::fromUtf8("_lvwNames"));

    hboxLayout->addWidget(_lvwNames);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    _btnUp = new QPushButton(InitiativeOrderDlgUi);
    _btnUp->setObjectName(QString::fromUtf8("_btnUp"));

    vboxLayout->addWidget(_btnUp);

    _btnDown = new QPushButton(InitiativeOrderDlgUi);
    _btnDown->setObjectName(QString::fromUtf8("_btnDown"));

    vboxLayout->addWidget(_btnDown);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem);

    _btnDone = new QPushButton(InitiativeOrderDlgUi);
    _btnDone->setObjectName(QString::fromUtf8("_btnDone"));

    vboxLayout->addWidget(_btnDone);


    hboxLayout->addLayout(vboxLayout);


    retranslateUi(InitiativeOrderDlgUi);
    QObject::connect(_btnDone, SIGNAL(clicked()), InitiativeOrderDlgUi, SLOT(accept()));

    QMetaObject::connectSlotsByName(InitiativeOrderDlgUi);
    } // setupUi

    void retranslateUi(QDialog *InitiativeOrderDlgUi)
    {
    InitiativeOrderDlgUi->setWindowTitle(QApplication::translate("InitiativeOrderDlgUi", "Dialog", 0, QApplication::UnicodeUTF8));
    _btnUp->setText(QApplication::translate("InitiativeOrderDlgUi", "Up", 0, QApplication::UnicodeUTF8));
    _btnDown->setText(QApplication::translate("InitiativeOrderDlgUi", "Down", 0, QApplication::UnicodeUTF8));
    _btnDone->setText(QApplication::translate("InitiativeOrderDlgUi", "Done", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(InitiativeOrderDlgUi);
    } // retranslateUi

};

namespace Ui {
    class InitiativeOrderDlgUi: public Ui_InitiativeOrderDlgUi {};
} // namespace Ui

#endif // INITIATIVEORDERDLGUI_H
