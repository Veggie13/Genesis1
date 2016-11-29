/********************************************************************************
** Form generated from reading ui file 'SoundboardAreaUi.ui'
**
** Created: Fri Aug 14 22:05:45 2009
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef SOUNDBOARDAREAUI_H
#define SOUNDBOARDAREAUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_SoundboardAreaUi
{
public:
    QGridLayout *gridLayout;
    QSplitter *m_tabArea;
    QFrame *frame;
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QTabWidget *m_generalTabs;
    QWidget *tab;
    QFrame *frame2;
    QVBoxLayout *vboxLayout1;
    QLabel *label_2;
    QTabWidget *m_sceneTabs;
    QWidget *tab_3;

    void setupUi(QWidget *SoundboardAreaUi)
    {
    if (SoundboardAreaUi->objectName().isEmpty())
        SoundboardAreaUi->setObjectName(QString::fromUtf8("SoundboardAreaUi"));
    gridLayout = new QGridLayout(SoundboardAreaUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    m_tabArea = new QSplitter(SoundboardAreaUi);
    m_tabArea->setObjectName(QString::fromUtf8("m_tabArea"));
    m_tabArea->setOrientation(Qt::Horizontal);
    frame = new QFrame(m_tabArea);
    frame->setObjectName(QString::fromUtf8("frame"));
    vboxLayout = new QVBoxLayout(frame);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(-1, -1, 0, -1);
    label = new QLabel(frame);
    label->setObjectName(QString::fromUtf8("label"));

    vboxLayout->addWidget(label);

    m_generalTabs = new QTabWidget(frame);
    m_generalTabs->setObjectName(QString::fromUtf8("m_generalTabs"));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    m_generalTabs->addTab(tab, QString());

    vboxLayout->addWidget(m_generalTabs);

    m_tabArea->addWidget(frame);
    frame2 = new QFrame(m_tabArea);
    frame2->setObjectName(QString::fromUtf8("frame2"));
    vboxLayout1 = new QVBoxLayout(frame2);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    vboxLayout1->setContentsMargins(0, -1, -1, -1);
    label_2 = new QLabel(frame2);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    vboxLayout1->addWidget(label_2);

    m_sceneTabs = new QTabWidget(frame2);
    m_sceneTabs->setObjectName(QString::fromUtf8("m_sceneTabs"));
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    m_sceneTabs->addTab(tab_3, QString());

    vboxLayout1->addWidget(m_sceneTabs);

    m_tabArea->addWidget(frame2);

    gridLayout->addWidget(m_tabArea, 0, 0, 1, 1);


    retranslateUi(SoundboardAreaUi);

    m_generalTabs->setCurrentIndex(0);
    m_sceneTabs->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(SoundboardAreaUi);
    } // setupUi

    void retranslateUi(QWidget *SoundboardAreaUi)
    {
    label->setText(QApplication::translate("SoundboardAreaUi", "General", 0, QApplication::UnicodeUTF8));
    m_generalTabs->setTabText(m_generalTabs->indexOf(tab), QApplication::translate("SoundboardAreaUi", "Tab 1", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SoundboardAreaUi", "Scene", 0, QApplication::UnicodeUTF8));
    m_sceneTabs->setTabText(m_sceneTabs->indexOf(tab_3), QApplication::translate("SoundboardAreaUi", "Tab 1", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SoundboardAreaUi);
    } // retranslateUi

};

namespace Ui {
    class SoundboardAreaUi: public Ui_SoundboardAreaUi {};
} // namespace Ui

#endif // SOUNDBOARDAREAUI_H
