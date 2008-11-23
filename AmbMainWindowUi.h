/********************************************************************************
** Form generated from reading ui file 'AmbMainWindowUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef AMBMAINWINDOWUI_H
#define AMBMAINWINDOWUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

class Ui_AmbMainWindowUi
{
public:
    QAction *m_exitAction;
    QAction *m_aboutAction;
    QAction *m_scenesAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_openAction;
    QAction *m_newAction;
    QAction *m_longAction;
    QAction *m_shortAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *m_mainWidgetFrm;
    QFrame *line;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *m_switchBtn;
    QComboBox *m_sceneCbo;
    QComboBox *m_stateCbo;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *m_recentFilesMenu;
    QMenu *menuHelp;
    QMenu *menuEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AmbMainWindowUi)
    {
    if (AmbMainWindowUi->objectName().isEmpty())
        AmbMainWindowUi->setObjectName(QString::fromUtf8("AmbMainWindowUi"));
    QSize size(418, 339);
    size = size.expandedTo(AmbMainWindowUi->minimumSizeHint());
    AmbMainWindowUi->resize(size);
    AmbMainWindowUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_sm.png")));
    m_exitAction = new QAction(AmbMainWindowUi);
    m_exitAction->setObjectName(QString::fromUtf8("m_exitAction"));
    m_aboutAction = new QAction(AmbMainWindowUi);
    m_aboutAction->setObjectName(QString::fromUtf8("m_aboutAction"));
    m_scenesAction = new QAction(AmbMainWindowUi);
    m_scenesAction->setObjectName(QString::fromUtf8("m_scenesAction"));
    m_saveAction = new QAction(AmbMainWindowUi);
    m_saveAction->setObjectName(QString::fromUtf8("m_saveAction"));
    m_saveAsAction = new QAction(AmbMainWindowUi);
    m_saveAsAction->setObjectName(QString::fromUtf8("m_saveAsAction"));
    m_openAction = new QAction(AmbMainWindowUi);
    m_openAction->setObjectName(QString::fromUtf8("m_openAction"));
    m_newAction = new QAction(AmbMainWindowUi);
    m_newAction->setObjectName(QString::fromUtf8("m_newAction"));
    m_longAction = new QAction(AmbMainWindowUi);
    m_longAction->setObjectName(QString::fromUtf8("m_longAction"));
    m_shortAction = new QAction(AmbMainWindowUi);
    m_shortAction->setObjectName(QString::fromUtf8("m_shortAction"));
    centralwidget = new QWidget(AmbMainWindowUi);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    gridLayout = new QGridLayout(centralwidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    m_mainWidgetFrm = new QFrame(centralwidget);
    m_mainWidgetFrm->setObjectName(QString::fromUtf8("m_mainWidgetFrm"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_mainWidgetFrm->sizePolicy().hasHeightForWidth());
    m_mainWidgetFrm->setSizePolicy(sizePolicy);
    m_mainWidgetFrm->setFrameShape(QFrame::NoFrame);

    gridLayout->addWidget(m_mainWidgetFrm, 0, 0, 1, 3);

    line = new QFrame(centralwidget);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line, 1, 0, 1, 3);

    label_2 = new QLabel(centralwidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
    label_2->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(label_2, 2, 0, 1, 1);

    label_3 = new QLabel(centralwidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
    label_3->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(label_3, 2, 1, 1, 1);

    m_switchBtn = new QPushButton(centralwidget);
    m_switchBtn->setObjectName(QString::fromUtf8("m_switchBtn"));
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(m_switchBtn->sizePolicy().hasHeightForWidth());
    m_switchBtn->setSizePolicy(sizePolicy2);

    gridLayout->addWidget(m_switchBtn, 2, 2, 2, 1);

    m_sceneCbo = new QComboBox(centralwidget);
    m_sceneCbo->setObjectName(QString::fromUtf8("m_sceneCbo"));
    QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(m_sceneCbo->sizePolicy().hasHeightForWidth());
    m_sceneCbo->setSizePolicy(sizePolicy3);

    gridLayout->addWidget(m_sceneCbo, 3, 0, 1, 1);

    m_stateCbo = new QComboBox(centralwidget);
    m_stateCbo->setObjectName(QString::fromUtf8("m_stateCbo"));
    sizePolicy3.setHeightForWidth(m_stateCbo->sizePolicy().hasHeightForWidth());
    m_stateCbo->setSizePolicy(sizePolicy3);

    gridLayout->addWidget(m_stateCbo, 3, 1, 1, 1);

    AmbMainWindowUi->setCentralWidget(centralwidget);
    menubar = new QMenuBar(AmbMainWindowUi);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 418, 19));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    m_recentFilesMenu = new QMenu(menuFile);
    m_recentFilesMenu->setObjectName(QString::fromUtf8("m_recentFilesMenu"));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    menuEdit = new QMenu(menubar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
    AmbMainWindowUi->setMenuBar(menubar);
    statusbar = new QStatusBar(AmbMainWindowUi);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    AmbMainWindowUi->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuEdit->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menuFile->addAction(m_newAction);
    menuFile->addAction(m_openAction);
    menuFile->addAction(m_saveAction);
    menuFile->addAction(m_saveAsAction);
    menuFile->addSeparator();
    menuFile->addAction(m_recentFilesMenu->menuAction());
    menuFile->addSeparator();
    menuFile->addAction(m_exitAction);
    menuHelp->addAction(m_aboutAction);
    menuEdit->addAction(m_scenesAction);
    menuEdit->addAction(m_longAction);
    menuEdit->addAction(m_shortAction);

    retranslateUi(AmbMainWindowUi);
    QObject::connect(m_exitAction, SIGNAL(activated()), AmbMainWindowUi, SLOT(close()));

    QMetaObject::connectSlotsByName(AmbMainWindowUi);
    } // setupUi

    void retranslateUi(QMainWindow *AmbMainWindowUi)
    {
    m_exitAction->setText(QApplication::translate("AmbMainWindowUi", "Exit", 0, QApplication::UnicodeUTF8));
    m_aboutAction->setText(QApplication::translate("AmbMainWindowUi", "About", 0, QApplication::UnicodeUTF8));
    m_scenesAction->setText(QApplication::translate("AmbMainWindowUi", "Scenes && States", 0, QApplication::UnicodeUTF8));
    m_saveAction->setText(QApplication::translate("AmbMainWindowUi", "Save", 0, QApplication::UnicodeUTF8));
    m_saveAsAction->setText(QApplication::translate("AmbMainWindowUi", "Save As", 0, QApplication::UnicodeUTF8));
    m_openAction->setText(QApplication::translate("AmbMainWindowUi", "Open", 0, QApplication::UnicodeUTF8));
    m_newAction->setText(QApplication::translate("AmbMainWindowUi", "New", 0, QApplication::UnicodeUTF8));
    m_longAction->setText(QApplication::translate("AmbMainWindowUi", "Streamed Imports", 0, QApplication::UnicodeUTF8));
    m_shortAction->setText(QApplication::translate("AmbMainWindowUi", "Sampled Imports", 0, QApplication::UnicodeUTF8));
    centralwidget->setWindowTitle(QApplication::translate("AmbMainWindowUi", "Ambient Sound Studio", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("AmbMainWindowUi", "Scene:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("AmbMainWindowUi", "State:", 0, QApplication::UnicodeUTF8));
    m_switchBtn->setText(QApplication::translate("AmbMainWindowUi", "Switch", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("AmbMainWindowUi", "File", 0, QApplication::UnicodeUTF8));
    m_recentFilesMenu->setTitle(QApplication::translate("AmbMainWindowUi", "Recent Files", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("AmbMainWindowUi", "Help", 0, QApplication::UnicodeUTF8));
    menuEdit->setTitle(QApplication::translate("AmbMainWindowUi", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AmbMainWindowUi: public Ui_AmbMainWindowUi {};
} // namespace Ui

#endif // AMBMAINWINDOWUI_H
