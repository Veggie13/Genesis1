/********************************************************************************
** Form generated from reading ui file 'AmbSplashUi.ui'
**
** Created: Sun Nov 23 00:27:40 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef AMBSPLASHUI_H
#define AMBSPLASHUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

class Ui_AmbSplashUi
{
public:
    QGridLayout *gridLayout;
    QLabel *m_splashImgLbl;
    QLabel *label;

    void setupUi(QWidget *AmbSplashUi)
    {
    if (AmbSplashUi->objectName().isEmpty())
        AmbSplashUi->setObjectName(QString::fromUtf8("AmbSplashUi"));
    QSize size(406, 510);
    size = size.expandedTo(AmbSplashUi->minimumSizeHint());
    AmbSplashUi->resize(size);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(AmbSplashUi->sizePolicy().hasHeightForWidth());
    AmbSplashUi->setSizePolicy(sizePolicy);
    gridLayout = new QGridLayout(AmbSplashUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    m_splashImgLbl = new QLabel(AmbSplashUi);
    m_splashImgLbl->setObjectName(QString::fromUtf8("m_splashImgLbl"));
    sizePolicy.setHeightForWidth(m_splashImgLbl->sizePolicy().hasHeightForWidth());
    m_splashImgLbl->setSizePolicy(sizePolicy);
    m_splashImgLbl->setFrameShape(QFrame::StyledPanel);
    m_splashImgLbl->setFrameShadow(QFrame::Sunken);
    m_splashImgLbl->setPixmap(QPixmap(QString::fromUtf8(":/images/genesis_splash.png")));

    gridLayout->addWidget(m_splashImgLbl, 0, 0, 1, 1);

    label = new QLabel(AmbSplashUi);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 1, 0, 1, 1);


    retranslateUi(AmbSplashUi);

    QMetaObject::connectSlotsByName(AmbSplashUi);
    } // setupUi

    void retranslateUi(QWidget *AmbSplashUi)
    {
    m_splashImgLbl->setText(QString());
    label->setText(QApplication::translate("AmbSplashUi", "Loading Ambience...", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AmbSplashUi);
    } // retranslateUi

};

namespace Ui {
    class AmbSplashUi: public Ui_AmbSplashUi {};
} // namespace Ui

#endif // AMBSPLASHUI_H
