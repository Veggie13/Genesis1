/********************************************************************************
** Form generated from reading ui file 'ResizeTableDlgUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef RESIZETABLEDLGUI_H
#define RESIZETABLEDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

class Ui_ResizeTableDlgUi
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *m_rowSpin;
    QLabel *label_2;
    QSpinBox *m_colSpin;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ResizeTableDlgUi)
    {
    if (ResizeTableDlgUi->objectName().isEmpty())
        ResizeTableDlgUi->setObjectName(QString::fromUtf8("ResizeTableDlgUi"));
    ResizeTableDlgUi->setWindowModality(Qt::ApplicationModal);
    QSize size(178, 96);
    size = size.expandedTo(ResizeTableDlgUi->minimumSizeHint());
    ResizeTableDlgUi->resize(size);
    ResizeTableDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    gridLayout = new QGridLayout(ResizeTableDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(ResizeTableDlgUi);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    m_rowSpin = new QSpinBox(ResizeTableDlgUi);
    m_rowSpin->setObjectName(QString::fromUtf8("m_rowSpin"));
    m_rowSpin->setMinimum(1);
    m_rowSpin->setMaximum(32);

    gridLayout->addWidget(m_rowSpin, 0, 1, 1, 1);

    label_2 = new QLabel(ResizeTableDlgUi);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout->addWidget(label_2, 1, 0, 1, 1);

    m_colSpin = new QSpinBox(ResizeTableDlgUi);
    m_colSpin->setObjectName(QString::fromUtf8("m_colSpin"));
    m_colSpin->setMinimum(1);
    m_colSpin->setMaximum(32);

    gridLayout->addWidget(m_colSpin, 1, 1, 1, 1);

    buttonBox = new QDialogButtonBox(ResizeTableDlgUi);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


    retranslateUi(ResizeTableDlgUi);
    QObject::connect(buttonBox, SIGNAL(accepted()), ResizeTableDlgUi, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), ResizeTableDlgUi, SLOT(reject()));

    QMetaObject::connectSlotsByName(ResizeTableDlgUi);
    } // setupUi

    void retranslateUi(QDialog *ResizeTableDlgUi)
    {
    ResizeTableDlgUi->setWindowTitle(QApplication::translate("ResizeTableDlgUi", "Resize Table", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ResizeTableDlgUi", "Rows", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ResizeTableDlgUi", "Columns", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ResizeTableDlgUi);
    } // retranslateUi

};

namespace Ui {
    class ResizeTableDlgUi: public Ui_ResizeTableDlgUi {};
} // namespace Ui

#endif // RESIZETABLEDLGUI_H
