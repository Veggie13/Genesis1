/********************************************************************************
** Form generated from reading ui file 'TitleDlgUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef TITLEDLGUI_H
#define TITLEDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

class Ui_TitleDlgUi
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *m_filenameLbl;
    QLineEdit *m_titleEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TitleDlgUi)
    {
    if (TitleDlgUi->objectName().isEmpty())
        TitleDlgUi->setObjectName(QString::fromUtf8("TitleDlgUi"));
    QSize size(345, 105);
    size = size.expandedTo(TitleDlgUi->minimumSizeHint());
    TitleDlgUi->resize(size);
    TitleDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    TitleDlgUi->setModal(true);
    gridLayout = new QGridLayout(TitleDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(TitleDlgUi);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy);

    gridLayout->addWidget(label, 0, 0, 1, 1);

    m_filenameLbl = new QLabel(TitleDlgUi);
    m_filenameLbl->setObjectName(QString::fromUtf8("m_filenameLbl"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(m_filenameLbl->sizePolicy().hasHeightForWidth());
    m_filenameLbl->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(m_filenameLbl, 0, 1, 1, 1);

    m_titleEdit = new QLineEdit(TitleDlgUi);
    m_titleEdit->setObjectName(QString::fromUtf8("m_titleEdit"));

    gridLayout->addWidget(m_titleEdit, 1, 0, 1, 2);

    buttonBox = new QDialogButtonBox(TitleDlgUi);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


    retranslateUi(TitleDlgUi);
    QObject::connect(buttonBox, SIGNAL(accepted()), TitleDlgUi, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), TitleDlgUi, SLOT(reject()));

    QMetaObject::connectSlotsByName(TitleDlgUi);
    } // setupUi

    void retranslateUi(QDialog *TitleDlgUi)
    {
    TitleDlgUi->setWindowTitle(QApplication::translate("TitleDlgUi", "Song Title", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("TitleDlgUi", "Choose a title for the file:", 0, QApplication::UnicodeUTF8));
    m_filenameLbl->setText(QString());
    Q_UNUSED(TitleDlgUi);
    } // retranslateUi

};

namespace Ui {
    class TitleDlgUi: public Ui_TitleDlgUi {};
} // namespace Ui

#endif // TITLEDLGUI_H
