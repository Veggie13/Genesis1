/********************************************************************************
** Form generated from reading ui file 'BackgroundCtrlUi.ui'
**
** Created: Sun Nov 23 00:27:40 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef BACKGROUNDCTRLUI_H
#define BACKGROUNDCTRLUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_BackgroundCtrlUi
{
public:
    QGridLayout *gridLayout;
    QListView *m_effectList;
    QVBoxLayout *vboxLayout;
    QLabel *label_2;
    QHBoxLayout *hboxLayout;
    QSlider *m_selectionVolSld;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    QCheckBox *m_selectionMuteChk;
    QSpacerItem *spacerItem1;
    QGridLayout *gridLayout1;
    QPushButton *m_selectAllBtn;
    QPushButton *m_deselectAllBtn;
    QPushButton *m_addBtn;
    QPushButton *m_deleteBtn;
    QFrame *line;
    QLabel *label_3;
    QSlider *m_globalVolSld;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem2;
    QCheckBox *m_backgroundGlobMute;
    QSpacerItem *spacerItem3;

    void setupUi(QWidget *BackgroundCtrlUi)
    {
    if (BackgroundCtrlUi->objectName().isEmpty())
        BackgroundCtrlUi->setObjectName(QString::fromUtf8("BackgroundCtrlUi"));
    QSize size(293, 204);
    size = size.expandedTo(BackgroundCtrlUi->minimumSizeHint());
    BackgroundCtrlUi->resize(size);
    gridLayout = new QGridLayout(BackgroundCtrlUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    m_effectList = new QListView(BackgroundCtrlUi);
    m_effectList->setObjectName(QString::fromUtf8("m_effectList"));
    m_effectList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_effectList->setSelectionBehavior(QAbstractItemView::SelectRows);

    gridLayout->addWidget(m_effectList, 0, 0, 1, 1);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    label_2 = new QLabel(BackgroundCtrlUi);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setAlignment(Qt::AlignCenter);

    vboxLayout->addWidget(label_2);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    m_selectionVolSld = new QSlider(BackgroundCtrlUi);
    m_selectionVolSld->setObjectName(QString::fromUtf8("m_selectionVolSld"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_selectionVolSld->sizePolicy().hasHeightForWidth());
    m_selectionVolSld->setSizePolicy(sizePolicy);
    m_selectionVolSld->setMaximum(100);
    m_selectionVolSld->setOrientation(Qt::Vertical);

    hboxLayout->addWidget(m_selectionVolSld);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem = new QSpacerItem(1, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem);

    m_selectionMuteChk = new QCheckBox(BackgroundCtrlUi);
    m_selectionMuteChk->setObjectName(QString::fromUtf8("m_selectionMuteChk"));

    hboxLayout1->addWidget(m_selectionMuteChk);

    spacerItem1 = new QSpacerItem(1, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);


    vboxLayout->addLayout(hboxLayout1);


    gridLayout->addLayout(vboxLayout, 0, 1, 2, 1);

    gridLayout1 = new QGridLayout();
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    m_selectAllBtn = new QPushButton(BackgroundCtrlUi);
    m_selectAllBtn->setObjectName(QString::fromUtf8("m_selectAllBtn"));

    gridLayout1->addWidget(m_selectAllBtn, 0, 0, 1, 1);

    m_deselectAllBtn = new QPushButton(BackgroundCtrlUi);
    m_deselectAllBtn->setObjectName(QString::fromUtf8("m_deselectAllBtn"));

    gridLayout1->addWidget(m_deselectAllBtn, 0, 1, 1, 1);

    m_addBtn = new QPushButton(BackgroundCtrlUi);
    m_addBtn->setObjectName(QString::fromUtf8("m_addBtn"));

    gridLayout1->addWidget(m_addBtn, 1, 0, 1, 1);

    m_deleteBtn = new QPushButton(BackgroundCtrlUi);
    m_deleteBtn->setObjectName(QString::fromUtf8("m_deleteBtn"));

    gridLayout1->addWidget(m_deleteBtn, 1, 1, 1, 1);


    gridLayout->addLayout(gridLayout1, 1, 0, 1, 1);

    line = new QFrame(BackgroundCtrlUi);
    line->setObjectName(QString::fromUtf8("line"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
    line->setSizePolicy(sizePolicy1);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line, 2, 0, 1, 2);

    label_3 = new QLabel(BackgroundCtrlUi);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
    label_3->setSizePolicy(sizePolicy2);

    gridLayout->addWidget(label_3, 3, 0, 1, 1);

    m_globalVolSld = new QSlider(BackgroundCtrlUi);
    m_globalVolSld->setObjectName(QString::fromUtf8("m_globalVolSld"));
    sizePolicy1.setHeightForWidth(m_globalVolSld->sizePolicy().hasHeightForWidth());
    m_globalVolSld->setSizePolicy(sizePolicy1);
    m_globalVolSld->setMaximum(100);
    m_globalVolSld->setValue(100);
    m_globalVolSld->setOrientation(Qt::Horizontal);

    gridLayout->addWidget(m_globalVolSld, 4, 0, 1, 1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    spacerItem2 = new QSpacerItem(1, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem2);

    m_backgroundGlobMute = new QCheckBox(BackgroundCtrlUi);
    m_backgroundGlobMute->setObjectName(QString::fromUtf8("m_backgroundGlobMute"));

    hboxLayout2->addWidget(m_backgroundGlobMute);

    spacerItem3 = new QSpacerItem(1, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem3);


    gridLayout->addLayout(hboxLayout2, 4, 1, 1, 1);


    retranslateUi(BackgroundCtrlUi);

    QMetaObject::connectSlotsByName(BackgroundCtrlUi);
    } // setupUi

    void retranslateUi(QWidget *BackgroundCtrlUi)
    {
    label_2->setText(QApplication::translate("BackgroundCtrlUi", "Selection Volume:", 0, QApplication::UnicodeUTF8));
    m_selectionMuteChk->setText(QApplication::translate("BackgroundCtrlUi", "Mute Selection", 0, QApplication::UnicodeUTF8));
    m_selectAllBtn->setText(QApplication::translate("BackgroundCtrlUi", "Select All", 0, QApplication::UnicodeUTF8));
    m_deselectAllBtn->setText(QApplication::translate("BackgroundCtrlUi", "Deselect All", 0, QApplication::UnicodeUTF8));
    m_addBtn->setText(QApplication::translate("BackgroundCtrlUi", "Add", 0, QApplication::UnicodeUTF8));
    m_deleteBtn->setText(QApplication::translate("BackgroundCtrlUi", "Delete", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("BackgroundCtrlUi", "Master:", 0, QApplication::UnicodeUTF8));
    m_backgroundGlobMute->setText(QApplication::translate("BackgroundCtrlUi", "Mute", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(BackgroundCtrlUi);
    } // retranslateUi

};

namespace Ui {
    class BackgroundCtrlUi: public Ui_BackgroundCtrlUi {};
} // namespace Ui

#endif // BACKGROUNDCTRLUI_H
