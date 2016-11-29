/********************************************************************************
** Form generated from reading ui file 'SessionViewUi.ui'
**
** Created: Thu Sep 16 21:31:01 2010
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef SESSIONVIEWUI_H
#define SESSIONVIEWUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "droptablewidget.qoh"
#include "panningviewwidget.h"

class Ui_SessionViewUi
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    DropTableWidget *_propertyTable;
    QFrame *_frmInitSequence;
    QVBoxLayout *vboxLayout1;
    QLabel *label;
    QSpacerItem *spacerItem;
    QFrame *_frmWaiters;
    QVBoxLayout *vboxLayout2;
    QLabel *label_2;
    QSpacerItem *spacerItem1;
    PanningViewWidget *_bottom;

    void setupUi(QWidget *SessionViewUi)
    {
    if (SessionViewUi->objectName().isEmpty())
        SessionViewUi->setObjectName(QString::fromUtf8("SessionViewUi"));
    QSize size(734, 394);
    size = size.expandedTo(SessionViewUi->minimumSizeHint());
    SessionViewUi->resize(size);
    vboxLayout = new QVBoxLayout(SessionViewUi);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    _propertyTable = new DropTableWidget(SessionViewUi);
    _propertyTable->setObjectName(QString::fromUtf8("_propertyTable"));
    _propertyTable->setEnabled(false);
    _propertyTable->setFocusPolicy(Qt::ClickFocus);
    _propertyTable->setAcceptDrops(true);
    _propertyTable->setDragDropMode(QAbstractItemView::DropOnly);
    _propertyTable->setSelectionMode(QAbstractItemView::NoSelection);

    hboxLayout->addWidget(_propertyTable);

    _frmInitSequence = new QFrame(SessionViewUi);
    _frmInitSequence->setObjectName(QString::fromUtf8("_frmInitSequence"));
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_frmInitSequence->sizePolicy().hasHeightForWidth());
    _frmInitSequence->setSizePolicy(sizePolicy);
    _frmInitSequence->setFrameShape(QFrame::NoFrame);
    _frmInitSequence->setFrameShadow(QFrame::Raised);
    vboxLayout1 = new QVBoxLayout(_frmInitSequence);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    label = new QLabel(_frmInitSequence);
    label->setObjectName(QString::fromUtf8("label"));

    vboxLayout1->addWidget(label);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem);


    hboxLayout->addWidget(_frmInitSequence);

    _frmWaiters = new QFrame(SessionViewUi);
    _frmWaiters->setObjectName(QString::fromUtf8("_frmWaiters"));
    sizePolicy.setHeightForWidth(_frmWaiters->sizePolicy().hasHeightForWidth());
    _frmWaiters->setSizePolicy(sizePolicy);
    _frmWaiters->setFrameShape(QFrame::NoFrame);
    _frmWaiters->setFrameShadow(QFrame::Plain);
    vboxLayout2 = new QVBoxLayout(_frmWaiters);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    label_2 = new QLabel(_frmWaiters);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    vboxLayout2->addWidget(label_2);

    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout2->addItem(spacerItem1);


    hboxLayout->addWidget(_frmWaiters);


    vboxLayout->addLayout(hboxLayout);

    _bottom = new PanningViewWidget(SessionViewUi);
    _bottom->setObjectName(QString::fromUtf8("_bottom"));
    _bottom->setMinimumSize(QSize(0, 40));

    vboxLayout->addWidget(_bottom);


    retranslateUi(SessionViewUi);

    QMetaObject::connectSlotsByName(SessionViewUi);
    } // setupUi

    void retranslateUi(QWidget *SessionViewUi)
    {
    SessionViewUi->setWindowTitle(QApplication::translate("SessionViewUi", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SessionViewUi", "Initiative", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SessionViewUi", "Waiting", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SessionViewUi);
    } // retranslateUi

};

namespace Ui {
    class SessionViewUi: public Ui_SessionViewUi {};
} // namespace Ui

#endif // SESSIONVIEWUI_H
