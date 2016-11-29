/********************************************************************************
** Form generated from reading ui file 'Test.ui'
**
** Created: Mon Sep 6 20:07:34 2010
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef TEST_H
#define TEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>
#include "droptablewidget.qoh"

class Ui_TestUi
{
public:
    DropTableWidget *tableWidget;
    QListWidget *listWidget;

    void setupUi(QWidget *TestUi)
    {
    if (TestUi->objectName().isEmpty())
        TestUi->setObjectName(QString::fromUtf8("TestUi"));
    QSize size(645, 300);
    size = size.expandedTo(TestUi->minimumSizeHint());
    TestUi->resize(size);
    tableWidget = new DropTableWidget(TestUi);
    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
    tableWidget->setGeometry(QRect(40, 20, 341, 192));
    tableWidget->setFocusPolicy(Qt::ClickFocus);
    tableWidget->setDragDropMode(QAbstractItemView::DropOnly);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setRowCount(3);
    tableWidget->setColumnCount(3);
    listWidget = new QListWidget(TestUi);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(455, 20, 161, 192));
    listWidget->setDragDropMode(QAbstractItemView::DragOnly);

    retranslateUi(TestUi);

    QMetaObject::connectSlotsByName(TestUi);
    } // setupUi

    void retranslateUi(QWidget *TestUi)
    {
    TestUi->setWindowTitle(QApplication::translate("TestUi", "Form", 0, QApplication::UnicodeUTF8));
    if (tableWidget->columnCount() < 3)
        tableWidget->setColumnCount(3);
    if (tableWidget->rowCount() < 3)
        tableWidget->setRowCount(3);
    listWidget->clear();

    QListWidgetItem *__item = new QListWidgetItem(listWidget);
    __item->setText(QApplication::translate("TestUi", "New Item", 0, QApplication::UnicodeUTF8));

    QListWidgetItem *__item1 = new QListWidgetItem(listWidget);
    __item1->setText(QApplication::translate("TestUi", "New Item", 0, QApplication::UnicodeUTF8));

    QListWidgetItem *__item2 = new QListWidgetItem(listWidget);
    __item2->setText(QApplication::translate("TestUi", "New Item2", 0, QApplication::UnicodeUTF8));

    QListWidgetItem *__item3 = new QListWidgetItem(listWidget);
    __item3->setText(QApplication::translate("TestUi", "New Item", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(TestUi);
    } // retranslateUi

};

namespace Ui {
    class TestUi: public Ui_TestUi {};
} // namespace Ui

#endif // TEST_H
