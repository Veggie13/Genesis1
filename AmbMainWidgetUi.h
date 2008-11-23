/********************************************************************************
** Form generated from reading ui file 'AmbMainWidgetUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef AMBMAINWIDGETUI_H
#define AMBMAINWIDGETUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_AmbMainWidgetUi
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QWidget *m_sndboardCtrl;
    QFrame *line;
    QToolButton *m_leftExpandBtn;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout1;
    QGroupBox *m_musicGrp;
    QGridLayout *gridLayout2;
    QWidget *m_musicCtrl;
    QGroupBox *m_backgroundGrp;
    QGridLayout *gridLayout3;
    QWidget *m_backgroundCtrl;
    QGroupBox *m_randomGrp;
    QGridLayout *gridLayout4;
    QWidget *m_randomCtrl;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;

    void setupUi(QWidget *AmbMainWidgetUi)
    {
    if (AmbMainWidgetUi->objectName().isEmpty())
        AmbMainWidgetUi->setObjectName(QString::fromUtf8("AmbMainWidgetUi"));
    QSize size(515, 488);
    size = size.expandedTo(AmbMainWidgetUi->minimumSizeHint());
    AmbMainWidgetUi->resize(size);
    gridLayout = new QGridLayout(AmbMainWidgetUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout1 = new QGridLayout();
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    label = new QLabel(AmbMainWidgetUi);
    label->setObjectName(QString::fromUtf8("label"));

    vboxLayout->addWidget(label);

    m_sndboardCtrl = new QWidget(AmbMainWidgetUi);
    m_sndboardCtrl->setObjectName(QString::fromUtf8("m_sndboardCtrl"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_sndboardCtrl->sizePolicy().hasHeightForWidth());
    m_sndboardCtrl->setSizePolicy(sizePolicy);

    vboxLayout->addWidget(m_sndboardCtrl);


    gridLayout1->addLayout(vboxLayout, 0, 3, 3, 1);

    line = new QFrame(AmbMainWidgetUi);
    line->setObjectName(QString::fromUtf8("line"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
    line->setSizePolicy(sizePolicy1);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout1->addWidget(line, 0, 2, 3, 1);

    m_leftExpandBtn = new QToolButton(AmbMainWidgetUi);
    m_leftExpandBtn->setObjectName(QString::fromUtf8("m_leftExpandBtn"));
    m_leftExpandBtn->setCheckable(true);

    gridLayout1->addWidget(m_leftExpandBtn, 0, 1, 1, 1);

    spacerItem = new QSpacerItem(1, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem, 0, 0, 1, 1);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    m_musicGrp = new QGroupBox(AmbMainWidgetUi);
    m_musicGrp->setObjectName(QString::fromUtf8("m_musicGrp"));
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(m_musicGrp->sizePolicy().hasHeightForWidth());
    m_musicGrp->setSizePolicy(sizePolicy2);
    gridLayout2 = new QGridLayout(m_musicGrp);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    m_musicCtrl = new QWidget(m_musicGrp);
    m_musicCtrl->setObjectName(QString::fromUtf8("m_musicCtrl"));

    gridLayout2->addWidget(m_musicCtrl, 0, 0, 1, 1);


    vboxLayout1->addWidget(m_musicGrp);

    m_backgroundGrp = new QGroupBox(AmbMainWidgetUi);
    m_backgroundGrp->setObjectName(QString::fromUtf8("m_backgroundGrp"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(m_backgroundGrp->sizePolicy().hasHeightForWidth());
    m_backgroundGrp->setSizePolicy(sizePolicy3);
    gridLayout3 = new QGridLayout(m_backgroundGrp);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    m_backgroundCtrl = new QWidget(m_backgroundGrp);
    m_backgroundCtrl->setObjectName(QString::fromUtf8("m_backgroundCtrl"));

    gridLayout3->addWidget(m_backgroundCtrl, 0, 0, 1, 1);


    vboxLayout1->addWidget(m_backgroundGrp);

    m_randomGrp = new QGroupBox(AmbMainWidgetUi);
    m_randomGrp->setObjectName(QString::fromUtf8("m_randomGrp"));
    sizePolicy3.setHeightForWidth(m_randomGrp->sizePolicy().hasHeightForWidth());
    m_randomGrp->setSizePolicy(sizePolicy3);
    gridLayout4 = new QGridLayout(m_randomGrp);
    gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
    m_randomCtrl = new QWidget(m_randomGrp);
    m_randomCtrl->setObjectName(QString::fromUtf8("m_randomCtrl"));

    gridLayout4->addWidget(m_randomCtrl, 0, 0, 1, 1);


    vboxLayout1->addWidget(m_randomGrp);


    gridLayout1->addLayout(vboxLayout1, 1, 0, 1, 2);

    spacerItem1 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

    gridLayout1->addItem(spacerItem1, 2, 0, 1, 1);

    spacerItem2 = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

    gridLayout1->addItem(spacerItem2, 2, 1, 1, 1);


    gridLayout->addLayout(gridLayout1, 0, 0, 1, 1);


    retranslateUi(AmbMainWidgetUi);

    QMetaObject::connectSlotsByName(AmbMainWidgetUi);
    } // setupUi

    void retranslateUi(QWidget *AmbMainWidgetUi)
    {
    label->setText(QApplication::translate("AmbMainWidgetUi", "Sound Board", 0, QApplication::UnicodeUTF8));
    m_musicGrp->setTitle(QApplication::translate("AmbMainWidgetUi", "Music", 0, QApplication::UnicodeUTF8));
    m_backgroundGrp->setTitle(QApplication::translate("AmbMainWidgetUi", "Background", 0, QApplication::UnicodeUTF8));
    m_randomGrp->setTitle(QApplication::translate("AmbMainWidgetUi", "Random", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AmbMainWidgetUi);
    } // retranslateUi

};

namespace Ui {
    class AmbMainWidgetUi: public Ui_AmbMainWidgetUi {};
} // namespace Ui

#endif // AMBMAINWIDGETUI_H
