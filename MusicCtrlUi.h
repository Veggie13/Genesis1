/********************************************************************************
** Form generated from reading ui file 'MusicCtrlUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef MUSICCTRLUI_H
#define MUSICCTRLUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

class Ui_MusicCtrlUi
{
public:
    QGridLayout *gridLayout;
    QComboBox *m_playlistCbo;
    QPushButton *m_addBtn;
    QPushButton *m_deleteBtn;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSlider *m_musicVolumeSld;
    QCheckBox *m_musicMuteChk;

    void setupUi(QWidget *MusicCtrlUi)
    {
    if (MusicCtrlUi->objectName().isEmpty())
        MusicCtrlUi->setObjectName(QString::fromUtf8("MusicCtrlUi"));
    QSize size(249, 70);
    size = size.expandedTo(MusicCtrlUi->minimumSizeHint());
    MusicCtrlUi->resize(size);
    gridLayout = new QGridLayout(MusicCtrlUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    m_playlistCbo = new QComboBox(MusicCtrlUi);
    m_playlistCbo->setObjectName(QString::fromUtf8("m_playlistCbo"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_playlistCbo->sizePolicy().hasHeightForWidth());
    m_playlistCbo->setSizePolicy(sizePolicy);

    gridLayout->addWidget(m_playlistCbo, 0, 0, 1, 1);

    m_addBtn = new QPushButton(MusicCtrlUi);
    m_addBtn->setObjectName(QString::fromUtf8("m_addBtn"));

    gridLayout->addWidget(m_addBtn, 0, 1, 1, 1);

    m_deleteBtn = new QPushButton(MusicCtrlUi);
    m_deleteBtn->setObjectName(QString::fromUtf8("m_deleteBtn"));

    gridLayout->addWidget(m_deleteBtn, 0, 2, 1, 1);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(MusicCtrlUi);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy1);

    hboxLayout->addWidget(label);

    m_musicVolumeSld = new QSlider(MusicCtrlUi);
    m_musicVolumeSld->setObjectName(QString::fromUtf8("m_musicVolumeSld"));
    sizePolicy.setHeightForWidth(m_musicVolumeSld->sizePolicy().hasHeightForWidth());
    m_musicVolumeSld->setSizePolicy(sizePolicy);
    m_musicVolumeSld->setMaximum(100);
    m_musicVolumeSld->setValue(100);
    m_musicVolumeSld->setOrientation(Qt::Horizontal);

    hboxLayout->addWidget(m_musicVolumeSld);


    gridLayout->addLayout(hboxLayout, 1, 0, 1, 2);

    m_musicMuteChk = new QCheckBox(MusicCtrlUi);
    m_musicMuteChk->setObjectName(QString::fromUtf8("m_musicMuteChk"));

    gridLayout->addWidget(m_musicMuteChk, 1, 2, 1, 1);


    retranslateUi(MusicCtrlUi);

    QMetaObject::connectSlotsByName(MusicCtrlUi);
    } // setupUi

    void retranslateUi(QWidget *MusicCtrlUi)
    {
    m_addBtn->setText(QApplication::translate("MusicCtrlUi", "Add...", 0, QApplication::UnicodeUTF8));
    m_deleteBtn->setText(QApplication::translate("MusicCtrlUi", "Delete", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("MusicCtrlUi", "Master:", 0, QApplication::UnicodeUTF8));
    m_musicMuteChk->setText(QApplication::translate("MusicCtrlUi", "Mute", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MusicCtrlUi);
    } // retranslateUi

};

namespace Ui {
    class MusicCtrlUi: public Ui_MusicCtrlUi {};
} // namespace Ui

#endif // MUSICCTRLUI_H
