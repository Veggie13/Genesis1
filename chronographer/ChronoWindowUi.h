/********************************************************************************
** Form generated from reading ui file 'ChronoWindowUi.ui'
**
** Created: Thu Sep 16 21:31:01 2010
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef CHRONOWINDOWUI_H
#define CHRONOWINDOWUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

class Ui_ChronoWindowUi
{
public:
    QAction *_actFileNew;
    QAction *_actFileLoad;
    QAction *_actFileSave;
    QAction *_actFileSaveAs;
    QAction *_actFileExit;
    QAction *_actProjectBeginSession;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *_mnuProject;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChronoWindowUi)
    {
    if (ChronoWindowUi->objectName().isEmpty())
        ChronoWindowUi->setObjectName(QString::fromUtf8("ChronoWindowUi"));
    QSize size(800, 600);
    size = size.expandedTo(ChronoWindowUi->minimumSizeHint());
    ChronoWindowUi->resize(size);
    _actFileNew = new QAction(ChronoWindowUi);
    _actFileNew->setObjectName(QString::fromUtf8("_actFileNew"));
    _actFileLoad = new QAction(ChronoWindowUi);
    _actFileLoad->setObjectName(QString::fromUtf8("_actFileLoad"));
    _actFileSave = new QAction(ChronoWindowUi);
    _actFileSave->setObjectName(QString::fromUtf8("_actFileSave"));
    _actFileSaveAs = new QAction(ChronoWindowUi);
    _actFileSaveAs->setObjectName(QString::fromUtf8("_actFileSaveAs"));
    _actFileExit = new QAction(ChronoWindowUi);
    _actFileExit->setObjectName(QString::fromUtf8("_actFileExit"));
    _actProjectBeginSession = new QAction(ChronoWindowUi);
    _actProjectBeginSession->setObjectName(QString::fromUtf8("_actProjectBeginSession"));
    centralwidget = new QWidget(ChronoWindowUi);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    ChronoWindowUi->setCentralWidget(centralwidget);
    menubar = new QMenuBar(ChronoWindowUi);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 19));
    menu_File = new QMenu(menubar);
    menu_File->setObjectName(QString::fromUtf8("menu_File"));
    _mnuProject = new QMenu(menubar);
    _mnuProject->setObjectName(QString::fromUtf8("_mnuProject"));
    ChronoWindowUi->setMenuBar(menubar);
    statusbar = new QStatusBar(ChronoWindowUi);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    ChronoWindowUi->setStatusBar(statusbar);

    menubar->addAction(menu_File->menuAction());
    menubar->addAction(_mnuProject->menuAction());
    menu_File->addAction(_actFileNew);
    menu_File->addAction(_actFileLoad);
    menu_File->addAction(_actFileSave);
    menu_File->addAction(_actFileSaveAs);
    menu_File->addSeparator();
    menu_File->addAction(_actFileExit);
    _mnuProject->addAction(_actProjectBeginSession);

    retranslateUi(ChronoWindowUi);
    QObject::connect(_actFileExit, SIGNAL(triggered()), ChronoWindowUi, SLOT(close()));

    QMetaObject::connectSlotsByName(ChronoWindowUi);
    } // setupUi

    void retranslateUi(QMainWindow *ChronoWindowUi)
    {
    ChronoWindowUi->setWindowTitle(QApplication::translate("ChronoWindowUi", "Chronographer", 0, QApplication::UnicodeUTF8));
    _actFileNew->setText(QApplication::translate("ChronoWindowUi", "&New", 0, QApplication::UnicodeUTF8));
    _actFileLoad->setText(QApplication::translate("ChronoWindowUi", "&Open Project", 0, QApplication::UnicodeUTF8));
    _actFileSave->setText(QApplication::translate("ChronoWindowUi", "&Save Project", 0, QApplication::UnicodeUTF8));
    _actFileSaveAs->setText(QApplication::translate("ChronoWindowUi", "Save Project &As...", 0, QApplication::UnicodeUTF8));
    _actFileExit->setText(QApplication::translate("ChronoWindowUi", "E&xit", 0, QApplication::UnicodeUTF8));
    _actProjectBeginSession->setText(QApplication::translate("ChronoWindowUi", "Begin &Session", 0, QApplication::UnicodeUTF8));
    menu_File->setTitle(QApplication::translate("ChronoWindowUi", "&File", 0, QApplication::UnicodeUTF8));
    _mnuProject->setTitle(QApplication::translate("ChronoWindowUi", "&Project", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChronoWindowUi: public Ui_ChronoWindowUi {};
} // namespace Ui

#endif // CHRONOWINDOWUI_H
