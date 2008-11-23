/********************************************************************************
** Form generated from reading ui file 'SoundboardUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef SOUNDBOARDUI_H
#define SOUNDBOARDUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_SoundboardUi
{
public:
    QVBoxLayout *vboxLayout;
    QTableWidget *m_buttonTbl;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSlider *m_sndboardVolumeSld;
    QPushButton *m_resizeBtn;

    void setupUi(QWidget *SoundboardUi)
    {
    if (SoundboardUi->objectName().isEmpty())
        SoundboardUi->setObjectName(QString::fromUtf8("SoundboardUi"));
    QSize size(155, 107);
    size = size.expandedTo(SoundboardUi->minimumSizeHint());
    SoundboardUi->resize(size);
    vboxLayout = new QVBoxLayout(SoundboardUi);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    m_buttonTbl = new QTableWidget(SoundboardUi);
    m_buttonTbl->setObjectName(QString::fromUtf8("m_buttonTbl"));
    QPalette palette;
    QBrush brush(QColor(192, 192, 192, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    m_buttonTbl->setPalette(palette);
    m_buttonTbl->setFrameShape(QFrame::NoFrame);
    m_buttonTbl->setFrameShadow(QFrame::Plain);
    m_buttonTbl->setLineWidth(0);
    m_buttonTbl->setMidLineWidth(2);
    m_buttonTbl->setGridStyle(Qt::NoPen);
    m_buttonTbl->setRowCount(16);
    m_buttonTbl->setColumnCount(8);

    vboxLayout->addWidget(m_buttonTbl);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(SoundboardUi);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);

    m_sndboardVolumeSld = new QSlider(SoundboardUi);
    m_sndboardVolumeSld->setObjectName(QString::fromUtf8("m_sndboardVolumeSld"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_sndboardVolumeSld->sizePolicy().hasHeightForWidth());
    m_sndboardVolumeSld->setSizePolicy(sizePolicy);
    m_sndboardVolumeSld->setMaximum(100);
    m_sndboardVolumeSld->setValue(100);
    m_sndboardVolumeSld->setOrientation(Qt::Horizontal);

    hboxLayout->addWidget(m_sndboardVolumeSld);

    m_resizeBtn = new QPushButton(SoundboardUi);
    m_resizeBtn->setObjectName(QString::fromUtf8("m_resizeBtn"));

    hboxLayout->addWidget(m_resizeBtn);


    vboxLayout->addLayout(hboxLayout);


    retranslateUi(SoundboardUi);

    QMetaObject::connectSlotsByName(SoundboardUi);
    } // setupUi

    void retranslateUi(QWidget *SoundboardUi)
    {
    if (m_buttonTbl->columnCount() < 8)
        m_buttonTbl->setColumnCount(8);
    if (m_buttonTbl->rowCount() < 16)
        m_buttonTbl->setRowCount(16);
    label->setText(QApplication::translate("SoundboardUi", "Volume:", 0, QApplication::UnicodeUTF8));
    m_resizeBtn->setText(QApplication::translate("SoundboardUi", "Resize Table", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SoundboardUi);
    } // retranslateUi

};

namespace Ui {
    class SoundboardUi: public Ui_SoundboardUi {};
} // namespace Ui

#endif // SOUNDBOARDUI_H
