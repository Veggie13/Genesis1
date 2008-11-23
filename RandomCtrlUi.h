/********************************************************************************
** Form generated from reading ui file 'RandomCtrlUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef RANDOMCTRLUI_H
#define RANDOMCTRLUI_H

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

class Ui_RandomCtrlUi
{
public:
    QGridLayout *gridLayout;
    QListView *m_effectList;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QLabel *label_2;
    QHBoxLayout *hboxLayout1;
    QSlider *m_selectionVolSld;
    QVBoxLayout *vboxLayout1;
    QLabel *label;
    QHBoxLayout *hboxLayout2;
    QSlider *m_selectionPerSld;
    QVBoxLayout *vboxLayout2;
    QLabel *label_4;
    QHBoxLayout *hboxLayout3;
    QSlider *m_selectionVarSld;
    QGridLayout *gridLayout1;
    QPushButton *m_selectAllBtn;
    QPushButton *m_deselectAllBtn;
    QPushButton *m_addBtn;
    QPushButton *m_deleteBtn;
    QHBoxLayout *hboxLayout4;
    QSpacerItem *spacerItem;
    QCheckBox *m_selectionMuteChk;
    QSpacerItem *spacerItem1;
    QFrame *line;
    QLabel *label_3;
    QSlider *m_globalVolSld;
    QHBoxLayout *hboxLayout5;
    QSpacerItem *spacerItem2;
    QCheckBox *m_globalMuteChk;
    QSpacerItem *spacerItem3;

    void setupUi(QWidget *RandomCtrlUi)
    {
    if (RandomCtrlUi->objectName().isEmpty())
        RandomCtrlUi->setObjectName(QString::fromUtf8("RandomCtrlUi"));
    QSize size(340, 204);
    size = size.expandedTo(RandomCtrlUi->minimumSizeHint());
    RandomCtrlUi->resize(size);
    gridLayout = new QGridLayout(RandomCtrlUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    m_effectList = new QListView(RandomCtrlUi);
    m_effectList->setObjectName(QString::fromUtf8("m_effectList"));
    m_effectList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_effectList->setSelectionBehavior(QAbstractItemView::SelectRows);

    gridLayout->addWidget(m_effectList, 0, 0, 1, 1);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    label_2 = new QLabel(RandomCtrlUi);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setAlignment(Qt::AlignCenter);

    vboxLayout->addWidget(label_2);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    m_selectionVolSld = new QSlider(RandomCtrlUi);
    m_selectionVolSld->setObjectName(QString::fromUtf8("m_selectionVolSld"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_selectionVolSld->sizePolicy().hasHeightForWidth());
    m_selectionVolSld->setSizePolicy(sizePolicy);
    m_selectionVolSld->setMaximum(100);
    m_selectionVolSld->setOrientation(Qt::Vertical);

    hboxLayout1->addWidget(m_selectionVolSld);


    vboxLayout->addLayout(hboxLayout1);


    hboxLayout->addLayout(vboxLayout);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    label = new QLabel(RandomCtrlUi);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);

    vboxLayout1->addWidget(label);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    m_selectionPerSld = new QSlider(RandomCtrlUi);
    m_selectionPerSld->setObjectName(QString::fromUtf8("m_selectionPerSld"));
    sizePolicy.setHeightForWidth(m_selectionPerSld->sizePolicy().hasHeightForWidth());
    m_selectionPerSld->setSizePolicy(sizePolicy);
    m_selectionPerSld->setMaximum(100);
    m_selectionPerSld->setOrientation(Qt::Vertical);

    hboxLayout2->addWidget(m_selectionPerSld);


    vboxLayout1->addLayout(hboxLayout2);


    hboxLayout->addLayout(vboxLayout1);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    label_4 = new QLabel(RandomCtrlUi);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setAlignment(Qt::AlignCenter);

    vboxLayout2->addWidget(label_4);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    m_selectionVarSld = new QSlider(RandomCtrlUi);
    m_selectionVarSld->setObjectName(QString::fromUtf8("m_selectionVarSld"));
    sizePolicy.setHeightForWidth(m_selectionVarSld->sizePolicy().hasHeightForWidth());
    m_selectionVarSld->setSizePolicy(sizePolicy);
    m_selectionVarSld->setMaximum(100);
    m_selectionVarSld->setOrientation(Qt::Vertical);

    hboxLayout3->addWidget(m_selectionVarSld);


    vboxLayout2->addLayout(hboxLayout3);


    hboxLayout->addLayout(vboxLayout2);


    gridLayout->addLayout(hboxLayout, 0, 1, 2, 1);

    gridLayout1 = new QGridLayout();
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    m_selectAllBtn = new QPushButton(RandomCtrlUi);
    m_selectAllBtn->setObjectName(QString::fromUtf8("m_selectAllBtn"));

    gridLayout1->addWidget(m_selectAllBtn, 0, 0, 1, 1);

    m_deselectAllBtn = new QPushButton(RandomCtrlUi);
    m_deselectAllBtn->setObjectName(QString::fromUtf8("m_deselectAllBtn"));

    gridLayout1->addWidget(m_deselectAllBtn, 0, 1, 1, 1);

    m_addBtn = new QPushButton(RandomCtrlUi);
    m_addBtn->setObjectName(QString::fromUtf8("m_addBtn"));

    gridLayout1->addWidget(m_addBtn, 1, 0, 1, 1);

    m_deleteBtn = new QPushButton(RandomCtrlUi);
    m_deleteBtn->setObjectName(QString::fromUtf8("m_deleteBtn"));

    gridLayout1->addWidget(m_deleteBtn, 1, 1, 1, 1);


    gridLayout->addLayout(gridLayout1, 1, 0, 2, 1);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    spacerItem = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

    hboxLayout4->addItem(spacerItem);

    m_selectionMuteChk = new QCheckBox(RandomCtrlUi);
    m_selectionMuteChk->setObjectName(QString::fromUtf8("m_selectionMuteChk"));

    hboxLayout4->addWidget(m_selectionMuteChk);

    spacerItem1 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

    hboxLayout4->addItem(spacerItem1);


    gridLayout->addLayout(hboxLayout4, 2, 1, 1, 1);

    line = new QFrame(RandomCtrlUi);
    line->setObjectName(QString::fromUtf8("line"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
    line->setSizePolicy(sizePolicy1);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line, 3, 0, 1, 2);

    label_3 = new QLabel(RandomCtrlUi);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
    label_3->setSizePolicy(sizePolicy2);

    gridLayout->addWidget(label_3, 4, 0, 1, 1);

    m_globalVolSld = new QSlider(RandomCtrlUi);
    m_globalVolSld->setObjectName(QString::fromUtf8("m_globalVolSld"));
    sizePolicy1.setHeightForWidth(m_globalVolSld->sizePolicy().hasHeightForWidth());
    m_globalVolSld->setSizePolicy(sizePolicy1);
    m_globalVolSld->setMaximum(100);
    m_globalVolSld->setValue(100);
    m_globalVolSld->setOrientation(Qt::Horizontal);

    gridLayout->addWidget(m_globalVolSld, 5, 0, 1, 1);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    spacerItem2 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

    hboxLayout5->addItem(spacerItem2);

    m_globalMuteChk = new QCheckBox(RandomCtrlUi);
    m_globalMuteChk->setObjectName(QString::fromUtf8("m_globalMuteChk"));

    hboxLayout5->addWidget(m_globalMuteChk);

    spacerItem3 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

    hboxLayout5->addItem(spacerItem3);


    gridLayout->addLayout(hboxLayout5, 5, 1, 1, 1);


    retranslateUi(RandomCtrlUi);

    QMetaObject::connectSlotsByName(RandomCtrlUi);
    } // setupUi

    void retranslateUi(QWidget *RandomCtrlUi)
    {
    label_2->setText(QApplication::translate("RandomCtrlUi", "Volume:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("RandomCtrlUi", "Period:", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("RandomCtrlUi", "Variance:", 0, QApplication::UnicodeUTF8));
    m_selectAllBtn->setText(QApplication::translate("RandomCtrlUi", "Select All", 0, QApplication::UnicodeUTF8));
    m_deselectAllBtn->setText(QApplication::translate("RandomCtrlUi", "Deselect All", 0, QApplication::UnicodeUTF8));
    m_addBtn->setText(QApplication::translate("RandomCtrlUi", "Add", 0, QApplication::UnicodeUTF8));
    m_deleteBtn->setText(QApplication::translate("RandomCtrlUi", "Delete", 0, QApplication::UnicodeUTF8));
    m_selectionMuteChk->setText(QApplication::translate("RandomCtrlUi", "Mute Selection", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("RandomCtrlUi", "Master:", 0, QApplication::UnicodeUTF8));
    m_globalMuteChk->setText(QApplication::translate("RandomCtrlUi", "Mute", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(RandomCtrlUi);
    } // retranslateUi

};

namespace Ui {
    class RandomCtrlUi: public Ui_RandomCtrlUi {};
} // namespace Ui

#endif // RANDOMCTRLUI_H
