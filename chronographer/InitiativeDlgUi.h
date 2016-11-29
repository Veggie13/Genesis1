/********************************************************************************
** Form generated from reading ui file 'InitiativeDlgUi.ui'
**
** Created: Thu Sep 16 21:31:01 2010
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef INITIATIVEDLGUI_H
#define INITIATIVEDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>

class Ui_InitiativeDlgUi
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *_lblCharacterName;
    QLabel *label_2;
    QHBoxLayout *hboxLayout;
    QSpinBox *_spnInitiative;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem1;
    QPushButton *_btnOk;

    void setupUi(QDialog *InitiativeDlgUi)
    {
    if (InitiativeDlgUi->objectName().isEmpty())
        InitiativeDlgUi->setObjectName(QString::fromUtf8("InitiativeDlgUi"));
    QSize size(217, 103);
    size = size.expandedTo(InitiativeDlgUi->minimumSizeHint());
    InitiativeDlgUi->resize(size);
    InitiativeDlgUi->setModal(true);
    gridLayout = new QGridLayout(InitiativeDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(InitiativeDlgUi);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy);

    gridLayout->addWidget(label, 0, 0, 1, 1);

    _lblCharacterName = new QLabel(InitiativeDlgUi);
    _lblCharacterName->setObjectName(QString::fromUtf8("_lblCharacterName"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(_lblCharacterName->sizePolicy().hasHeightForWidth());
    _lblCharacterName->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(_lblCharacterName, 0, 1, 1, 1);

    label_2 = new QLabel(InitiativeDlgUi);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    _spnInitiative = new QSpinBox(InitiativeDlgUi);
    _spnInitiative->setObjectName(QString::fromUtf8("_spnInitiative"));
    _spnInitiative->setMinimum(-99);
    _spnInitiative->setValue(10);

    hboxLayout->addWidget(_spnInitiative);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);


    gridLayout->addLayout(hboxLayout, 1, 1, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);

    _btnOk = new QPushButton(InitiativeDlgUi);
    _btnOk->setObjectName(QString::fromUtf8("_btnOk"));

    hboxLayout1->addWidget(_btnOk);


    gridLayout->addLayout(hboxLayout1, 2, 1, 1, 1);


    retranslateUi(InitiativeDlgUi);
    QObject::connect(_btnOk, SIGNAL(clicked()), InitiativeDlgUi, SLOT(accept()));

    QMetaObject::connectSlotsByName(InitiativeDlgUi);
    } // setupUi

    void retranslateUi(QDialog *InitiativeDlgUi)
    {
    InitiativeDlgUi->setWindowTitle(QApplication::translate("InitiativeDlgUi", "Initiative", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("InitiativeDlgUi", "Character:", 0, QApplication::UnicodeUTF8));
    _lblCharacterName->setText(QString());
    label_2->setText(QApplication::translate("InitiativeDlgUi", "Initiative:", 0, QApplication::UnicodeUTF8));
    _btnOk->setText(QApplication::translate("InitiativeDlgUi", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(InitiativeDlgUi);
    } // retranslateUi

};

namespace Ui {
    class InitiativeDlgUi: public Ui_InitiativeDlgUi {};
} // namespace Ui

#endif // INITIATIVEDLGUI_H
