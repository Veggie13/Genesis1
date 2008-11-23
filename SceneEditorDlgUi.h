/********************************************************************************
** Form generated from reading ui file 'SceneEditorDlgUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef SCENEEDITORDLGUI_H
#define SCENEEDITORDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

class Ui_SceneEditorDlgUi
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *hboxLayout;
    QComboBox *m_sceneCbo;
    QPushButton *m_newSceneBtn;
    QPushButton *m_deleteSceneBtn;
    QGroupBox *m_statesGrp;
    QGridLayout *gridLayout1;
    QListView *m_stateList;
    QPushButton *m_newStateBtn;
    QPushButton *m_deleteStateBtn;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QPushButton *m_closeBtn;
    QSpacerItem *spacerItem2;

    void setupUi(QDialog *SceneEditorDlgUi)
    {
    if (SceneEditorDlgUi->objectName().isEmpty())
        SceneEditorDlgUi->setObjectName(QString::fromUtf8("SceneEditorDlgUi"));
    QSize size(400, 304);
    size = size.expandedTo(SceneEditorDlgUi->minimumSizeHint());
    SceneEditorDlgUi->resize(size);
    SceneEditorDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    SceneEditorDlgUi->setModal(true);
    gridLayout = new QGridLayout(SceneEditorDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(SceneEditorDlgUi);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 3);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    m_sceneCbo = new QComboBox(SceneEditorDlgUi);
    m_sceneCbo->setObjectName(QString::fromUtf8("m_sceneCbo"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_sceneCbo->sizePolicy().hasHeightForWidth());
    m_sceneCbo->setSizePolicy(sizePolicy);

    hboxLayout->addWidget(m_sceneCbo);

    m_newSceneBtn = new QPushButton(SceneEditorDlgUi);
    m_newSceneBtn->setObjectName(QString::fromUtf8("m_newSceneBtn"));

    hboxLayout->addWidget(m_newSceneBtn);

    m_deleteSceneBtn = new QPushButton(SceneEditorDlgUi);
    m_deleteSceneBtn->setObjectName(QString::fromUtf8("m_deleteSceneBtn"));

    hboxLayout->addWidget(m_deleteSceneBtn);


    gridLayout->addLayout(hboxLayout, 1, 0, 1, 3);

    m_statesGrp = new QGroupBox(SceneEditorDlgUi);
    m_statesGrp->setObjectName(QString::fromUtf8("m_statesGrp"));
    gridLayout1 = new QGridLayout(m_statesGrp);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    m_stateList = new QListView(m_statesGrp);
    m_stateList->setObjectName(QString::fromUtf8("m_stateList"));
    m_stateList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_stateList->setSelectionBehavior(QAbstractItemView::SelectRows);

    gridLayout1->addWidget(m_stateList, 0, 0, 3, 1);

    m_newStateBtn = new QPushButton(m_statesGrp);
    m_newStateBtn->setObjectName(QString::fromUtf8("m_newStateBtn"));

    gridLayout1->addWidget(m_newStateBtn, 0, 1, 1, 1);

    m_deleteStateBtn = new QPushButton(m_statesGrp);
    m_deleteStateBtn->setObjectName(QString::fromUtf8("m_deleteStateBtn"));

    gridLayout1->addWidget(m_deleteStateBtn, 1, 1, 1, 1);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout1->addItem(spacerItem, 2, 1, 1, 1);


    gridLayout->addWidget(m_statesGrp, 2, 0, 1, 3);

    spacerItem1 = new QSpacerItem(101, 26, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem1, 3, 0, 1, 1);

    m_closeBtn = new QPushButton(SceneEditorDlgUi);
    m_closeBtn->setObjectName(QString::fromUtf8("m_closeBtn"));

    gridLayout->addWidget(m_closeBtn, 3, 1, 1, 1);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem2, 3, 2, 1, 1);


    retranslateUi(SceneEditorDlgUi);
    QObject::connect(m_closeBtn, SIGNAL(clicked()), SceneEditorDlgUi, SLOT(accept()));

    QMetaObject::connectSlotsByName(SceneEditorDlgUi);
    } // setupUi

    void retranslateUi(QDialog *SceneEditorDlgUi)
    {
    SceneEditorDlgUi->setWindowTitle(QApplication::translate("SceneEditorDlgUi", "Scene Editor", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SceneEditorDlgUi", "Scenes", 0, QApplication::UnicodeUTF8));
    m_newSceneBtn->setText(QApplication::translate("SceneEditorDlgUi", "New...", 0, QApplication::UnicodeUTF8));
    m_deleteSceneBtn->setText(QApplication::translate("SceneEditorDlgUi", "Delete", 0, QApplication::UnicodeUTF8));
    m_statesGrp->setTitle(QApplication::translate("SceneEditorDlgUi", "States", 0, QApplication::UnicodeUTF8));
    m_newStateBtn->setText(QApplication::translate("SceneEditorDlgUi", "New...", 0, QApplication::UnicodeUTF8));
    m_deleteStateBtn->setText(QApplication::translate("SceneEditorDlgUi", "Delete", 0, QApplication::UnicodeUTF8));
    m_closeBtn->setText(QApplication::translate("SceneEditorDlgUi", "Close", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SceneEditorDlgUi);
    } // retranslateUi

};

namespace Ui {
    class SceneEditorDlgUi: public Ui_SceneEditorDlgUi {};
} // namespace Ui

#endif // SCENEEDITORDLGUI_H
