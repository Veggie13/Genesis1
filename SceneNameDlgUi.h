/********************************************************************************
** Form generated from reading ui file 'SceneNameDlgUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef SCENENAMEDLGUI_H
#define SCENENAMEDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

class Ui_SceneNameDlgUi
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *m_sceneNameEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SceneNameDlgUi)
    {
    if (SceneNameDlgUi->objectName().isEmpty())
        SceneNameDlgUi->setObjectName(QString::fromUtf8("SceneNameDlgUi"));
    QSize size(312, 92);
    size = size.expandedTo(SceneNameDlgUi->minimumSizeHint());
    SceneNameDlgUi->resize(size);
    SceneNameDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    SceneNameDlgUi->setModal(true);
    gridLayout = new QGridLayout(SceneNameDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(SceneNameDlgUi);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    m_sceneNameEdit = new QLineEdit(SceneNameDlgUi);
    m_sceneNameEdit->setObjectName(QString::fromUtf8("m_sceneNameEdit"));

    gridLayout->addWidget(m_sceneNameEdit, 1, 0, 1, 1);

    buttonBox = new QDialogButtonBox(SceneNameDlgUi);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


    retranslateUi(SceneNameDlgUi);
    QObject::connect(buttonBox, SIGNAL(accepted()), SceneNameDlgUi, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), SceneNameDlgUi, SLOT(reject()));

    QMetaObject::connectSlotsByName(SceneNameDlgUi);
    } // setupUi

    void retranslateUi(QDialog *SceneNameDlgUi)
    {
    SceneNameDlgUi->setWindowTitle(QApplication::translate("SceneNameDlgUi", "New Scene", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SceneNameDlgUi", "Please name the new scene:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SceneNameDlgUi);
    } // retranslateUi

};

namespace Ui {
    class SceneNameDlgUi: public Ui_SceneNameDlgUi {};
} // namespace Ui

#endif // SCENENAMEDLGUI_H
