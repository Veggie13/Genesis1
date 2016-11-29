/********************************************************************************
** Form generated from reading ui file 'MakeNoteDlgUi.ui'
**
** Created: Thu Sep 16 21:31:01 2010
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef MAKENOTEDLGUI_H
#define MAKENOTEDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

class Ui_MakeNoteDlgUi
{
public:
    QVBoxLayout *vboxLayout;
    QTextEdit *_txtNote;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MakeNoteDlgUi)
    {
    if (MakeNoteDlgUi->objectName().isEmpty())
        MakeNoteDlgUi->setObjectName(QString::fromUtf8("MakeNoteDlgUi"));
    QSize size(400, 300);
    size = size.expandedTo(MakeNoteDlgUi->minimumSizeHint());
    MakeNoteDlgUi->resize(size);
    MakeNoteDlgUi->setSizeGripEnabled(true);
    MakeNoteDlgUi->setModal(true);
    vboxLayout = new QVBoxLayout(MakeNoteDlgUi);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    _txtNote = new QTextEdit(MakeNoteDlgUi);
    _txtNote->setObjectName(QString::fromUtf8("_txtNote"));
    _txtNote->setAcceptRichText(false);

    vboxLayout->addWidget(_txtNote);

    buttonBox = new QDialogButtonBox(MakeNoteDlgUi);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    vboxLayout->addWidget(buttonBox);


    retranslateUi(MakeNoteDlgUi);
    QObject::connect(buttonBox, SIGNAL(accepted()), MakeNoteDlgUi, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), MakeNoteDlgUi, SLOT(reject()));

    QMetaObject::connectSlotsByName(MakeNoteDlgUi);
    } // setupUi

    void retranslateUi(QDialog *MakeNoteDlgUi)
    {
    MakeNoteDlgUi->setWindowTitle(QApplication::translate("MakeNoteDlgUi", "Make a Note", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MakeNoteDlgUi);
    } // retranslateUi

};

namespace Ui {
    class MakeNoteDlgUi: public Ui_MakeNoteDlgUi {};
} // namespace Ui

#endif // MAKENOTEDLGUI_H
