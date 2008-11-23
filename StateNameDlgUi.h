/********************************************************************************
** Form generated from reading ui file 'StateNameDlgUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef STATENAMEDLGUI_H
#define STATENAMEDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

class Ui_StateNameDlgUi
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *m_stateNameEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *StateNameDlgUi)
    {
    if (StateNameDlgUi->objectName().isEmpty())
        StateNameDlgUi->setObjectName(QString::fromUtf8("StateNameDlgUi"));
    QSize size(312, 92);
    size = size.expandedTo(StateNameDlgUi->minimumSizeHint());
    StateNameDlgUi->resize(size);
    StateNameDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    StateNameDlgUi->setModal(true);
    gridLayout = new QGridLayout(StateNameDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(StateNameDlgUi);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    m_stateNameEdit = new QLineEdit(StateNameDlgUi);
    m_stateNameEdit->setObjectName(QString::fromUtf8("m_stateNameEdit"));

    gridLayout->addWidget(m_stateNameEdit, 1, 0, 1, 1);

    buttonBox = new QDialogButtonBox(StateNameDlgUi);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


    retranslateUi(StateNameDlgUi);
    QObject::connect(buttonBox, SIGNAL(accepted()), StateNameDlgUi, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), StateNameDlgUi, SLOT(reject()));

    QMetaObject::connectSlotsByName(StateNameDlgUi);
    } // setupUi

    void retranslateUi(QDialog *StateNameDlgUi)
    {
    StateNameDlgUi->setWindowTitle(QApplication::translate("StateNameDlgUi", "New State", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("StateNameDlgUi", "Please name the new state:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(StateNameDlgUi);
    } // retranslateUi

};

namespace Ui {
    class StateNameDlgUi: public Ui_StateNameDlgUi {};
} // namespace Ui

#endif // STATENAMEDLGUI_H
