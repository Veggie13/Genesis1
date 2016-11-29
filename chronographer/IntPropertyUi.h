/********************************************************************************
** Form generated from reading ui file 'IntPropertyUi.ui'
**
** Created: Thu Sep 16 21:31:01 2010
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef INTPROPERTYUI_H
#define INTPROPERTYUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_IntPropertyUi
{
public:
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QLineEdit *_edtValue;
    QLineEdit *_edtDelta;
    QVBoxLayout *vboxLayout;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout1;
    QPushButton *_btnPlus;
    QHBoxLayout *hboxLayout2;
    QPushButton *_btnMinus;
    QSpacerItem *spacerItem2;
    QSpacerItem *spacerItem3;

    void setupUi(QWidget *IntPropertyUi)
    {
    if (IntPropertyUi->objectName().isEmpty())
        IntPropertyUi->setObjectName(QString::fromUtf8("IntPropertyUi"));
    QSize size(98, 40);
    size = size.expandedTo(IntPropertyUi->minimumSizeHint());
    IntPropertyUi->resize(size);
    hboxLayout = new QHBoxLayout(IntPropertyUi);
    hboxLayout->setSpacing(2);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout->setContentsMargins(3, 1, 1, 1);
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    _edtValue = new QLineEdit(IntPropertyUi);
    _edtValue->setObjectName(QString::fromUtf8("_edtValue"));
    _edtValue->setAlignment(Qt::AlignCenter);

    hboxLayout->addWidget(_edtValue);

    _edtDelta = new QLineEdit(IntPropertyUi);
    _edtDelta->setObjectName(QString::fromUtf8("_edtDelta"));
    _edtDelta->setAlignment(Qt::AlignCenter);

    hboxLayout->addWidget(_edtDelta);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    _btnPlus = new QPushButton(IntPropertyUi);
    _btnPlus->setObjectName(QString::fromUtf8("_btnPlus"));
    _btnPlus->setMaximumSize(QSize(16, 16));

    hboxLayout1->addWidget(_btnPlus);


    vboxLayout->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    _btnMinus = new QPushButton(IntPropertyUi);
    _btnMinus->setObjectName(QString::fromUtf8("_btnMinus"));
    _btnMinus->setMaximumSize(QSize(16, 16));

    hboxLayout2->addWidget(_btnMinus);


    vboxLayout->addLayout(hboxLayout2);

    spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem2);


    hboxLayout->addLayout(vboxLayout);

    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem3);


    retranslateUi(IntPropertyUi);

    QMetaObject::connectSlotsByName(IntPropertyUi);
    } // setupUi

    void retranslateUi(QWidget *IntPropertyUi)
    {
    IntPropertyUi->setWindowTitle(QApplication::translate("IntPropertyUi", "Form", 0, QApplication::UnicodeUTF8));
    _btnPlus->setText(QApplication::translate("IntPropertyUi", "+", 0, QApplication::UnicodeUTF8));
    _btnMinus->setText(QApplication::translate("IntPropertyUi", "-", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(IntPropertyUi);
    } // retranslateUi

};

namespace Ui {
    class IntPropertyUi: public Ui_IntPropertyUi {};
} // namespace Ui

#endif // INTPROPERTYUI_H
