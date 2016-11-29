/********************************************************************************
** Form generated from reading ui file 'ProjectSetupViewUi.ui'
**
** Created: Thu Sep 16 21:31:01 2010
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef PROJECTSETUPVIEWUI_H
#define PROJECTSETUPVIEWUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_ProjectSetupViewUi
{
public:
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QListWidget *_lvwCharacters;
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout1;
    QPushButton *_btnCharRemove;
    QSpacerItem *spacerItem1;
    QPushButton *_btnCharEdit;
    QPushButton *_btnAddChar;
    QLineEdit *_edtCharName;
    QSpacerItem *spacerItem2;
    QVBoxLayout *vboxLayout1;
    QLabel *label_2;
    QListWidget *_lvwProperties;
    QGridLayout *gridLayout1;
    QComboBox *_cboPropTypes;
    QPushButton *_btnPropRemove;
    QLineEdit *_edtPropName;
    QPushButton *_btnAddProp;
    QPushButton *_btnPropEdit;
    QSpacerItem *spacerItem3;
    QVBoxLayout *vboxLayout2;
    QLabel *label_3;
    QListWidget *_lvwEvents;
    QGridLayout *gridLayout2;
    QHBoxLayout *hboxLayout2;
    QPushButton *_btnEventRemove;
    QSpacerItem *spacerItem4;
    QPushButton *_btnEventEdit;
    QPushButton *_btnAddEvent;
    QLineEdit *_edtEventName;
    QSpacerItem *spacerItem5;

    void setupUi(QWidget *ProjectSetupViewUi)
    {
    if (ProjectSetupViewUi->objectName().isEmpty())
        ProjectSetupViewUi->setObjectName(QString::fromUtf8("ProjectSetupViewUi"));
    QSize size(840, 492);
    size = size.expandedTo(ProjectSetupViewUi->minimumSizeHint());
    ProjectSetupViewUi->resize(size);
    hboxLayout = new QHBoxLayout(ProjectSetupViewUi);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(16, 457, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    label = new QLabel(ProjectSetupViewUi);
    label->setObjectName(QString::fromUtf8("label"));

    vboxLayout->addWidget(label);

    _lvwCharacters = new QListWidget(ProjectSetupViewUi);
    _lvwCharacters->setObjectName(QString::fromUtf8("_lvwCharacters"));
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_lvwCharacters->sizePolicy().hasHeightForWidth());
    _lvwCharacters->setSizePolicy(sizePolicy);

    vboxLayout->addWidget(_lvwCharacters);

    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    _btnCharRemove = new QPushButton(ProjectSetupViewUi);
    _btnCharRemove->setObjectName(QString::fromUtf8("_btnCharRemove"));

    hboxLayout1->addWidget(_btnCharRemove);

    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);


    gridLayout->addLayout(hboxLayout1, 0, 0, 1, 1);

    _btnCharEdit = new QPushButton(ProjectSetupViewUi);
    _btnCharEdit->setObjectName(QString::fromUtf8("_btnCharEdit"));

    gridLayout->addWidget(_btnCharEdit, 0, 1, 1, 1);

    _btnAddChar = new QPushButton(ProjectSetupViewUi);
    _btnAddChar->setObjectName(QString::fromUtf8("_btnAddChar"));

    gridLayout->addWidget(_btnAddChar, 1, 1, 1, 1);

    _edtCharName = new QLineEdit(ProjectSetupViewUi);
    _edtCharName->setObjectName(QString::fromUtf8("_edtCharName"));
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(_edtCharName->sizePolicy().hasHeightForWidth());
    _edtCharName->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(_edtCharName, 1, 0, 1, 1);


    vboxLayout->addLayout(gridLayout);


    hboxLayout->addLayout(vboxLayout);

    spacerItem2 = new QSpacerItem(16, 457, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem2);

    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    label_2 = new QLabel(ProjectSetupViewUi);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    vboxLayout1->addWidget(label_2);

    _lvwProperties = new QListWidget(ProjectSetupViewUi);
    _lvwProperties->setObjectName(QString::fromUtf8("_lvwProperties"));

    vboxLayout1->addWidget(_lvwProperties);

    gridLayout1 = new QGridLayout();
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    _cboPropTypes = new QComboBox(ProjectSetupViewUi);
    _cboPropTypes->setObjectName(QString::fromUtf8("_cboPropTypes"));

    gridLayout1->addWidget(_cboPropTypes, 1, 0, 1, 1);

    _btnPropRemove = new QPushButton(ProjectSetupViewUi);
    _btnPropRemove->setObjectName(QString::fromUtf8("_btnPropRemove"));

    gridLayout1->addWidget(_btnPropRemove, 0, 0, 1, 1);

    _edtPropName = new QLineEdit(ProjectSetupViewUi);
    _edtPropName->setObjectName(QString::fromUtf8("_edtPropName"));
    sizePolicy1.setHeightForWidth(_edtPropName->sizePolicy().hasHeightForWidth());
    _edtPropName->setSizePolicy(sizePolicy1);

    gridLayout1->addWidget(_edtPropName, 1, 1, 1, 1);

    _btnAddProp = new QPushButton(ProjectSetupViewUi);
    _btnAddProp->setObjectName(QString::fromUtf8("_btnAddProp"));

    gridLayout1->addWidget(_btnAddProp, 1, 2, 1, 1);

    _btnPropEdit = new QPushButton(ProjectSetupViewUi);
    _btnPropEdit->setObjectName(QString::fromUtf8("_btnPropEdit"));

    gridLayout1->addWidget(_btnPropEdit, 0, 2, 1, 1);


    vboxLayout1->addLayout(gridLayout1);


    hboxLayout->addLayout(vboxLayout1);

    spacerItem3 = new QSpacerItem(16, 457, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem3);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    label_3 = new QLabel(ProjectSetupViewUi);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    vboxLayout2->addWidget(label_3);

    _lvwEvents = new QListWidget(ProjectSetupViewUi);
    _lvwEvents->setObjectName(QString::fromUtf8("_lvwEvents"));
    sizePolicy.setHeightForWidth(_lvwEvents->sizePolicy().hasHeightForWidth());
    _lvwEvents->setSizePolicy(sizePolicy);

    vboxLayout2->addWidget(_lvwEvents);

    gridLayout2 = new QGridLayout();
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    _btnEventRemove = new QPushButton(ProjectSetupViewUi);
    _btnEventRemove->setObjectName(QString::fromUtf8("_btnEventRemove"));

    hboxLayout2->addWidget(_btnEventRemove);

    spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem4);


    gridLayout2->addLayout(hboxLayout2, 0, 0, 1, 1);

    _btnEventEdit = new QPushButton(ProjectSetupViewUi);
    _btnEventEdit->setObjectName(QString::fromUtf8("_btnEventEdit"));

    gridLayout2->addWidget(_btnEventEdit, 0, 1, 1, 1);

    _btnAddEvent = new QPushButton(ProjectSetupViewUi);
    _btnAddEvent->setObjectName(QString::fromUtf8("_btnAddEvent"));

    gridLayout2->addWidget(_btnAddEvent, 1, 1, 1, 1);

    _edtEventName = new QLineEdit(ProjectSetupViewUi);
    _edtEventName->setObjectName(QString::fromUtf8("_edtEventName"));
    sizePolicy1.setHeightForWidth(_edtEventName->sizePolicy().hasHeightForWidth());
    _edtEventName->setSizePolicy(sizePolicy1);

    gridLayout2->addWidget(_edtEventName, 1, 0, 1, 1);


    vboxLayout2->addLayout(gridLayout2);


    hboxLayout->addLayout(vboxLayout2);

    spacerItem5 = new QSpacerItem(16, 457, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem5);


    retranslateUi(ProjectSetupViewUi);

    QMetaObject::connectSlotsByName(ProjectSetupViewUi);
    } // setupUi

    void retranslateUi(QWidget *ProjectSetupViewUi)
    {
    ProjectSetupViewUi->setWindowTitle(QApplication::translate("ProjectSetupViewUi", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ProjectSetupViewUi", "Characters", 0, QApplication::UnicodeUTF8));
    _btnCharRemove->setText(QApplication::translate("ProjectSetupViewUi", "Remove", 0, QApplication::UnicodeUTF8));
    _btnCharEdit->setText(QApplication::translate("ProjectSetupViewUi", "Rename", 0, QApplication::UnicodeUTF8));
    _btnAddChar->setText(QApplication::translate("ProjectSetupViewUi", "Add", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ProjectSetupViewUi", "Properties", 0, QApplication::UnicodeUTF8));
    _btnPropRemove->setText(QApplication::translate("ProjectSetupViewUi", "Remove", 0, QApplication::UnicodeUTF8));
    _btnAddProp->setText(QApplication::translate("ProjectSetupViewUi", "Add", 0, QApplication::UnicodeUTF8));
    _btnPropEdit->setText(QApplication::translate("ProjectSetupViewUi", "Rename", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("ProjectSetupViewUi", "Custom Events", 0, QApplication::UnicodeUTF8));
    _btnEventRemove->setText(QApplication::translate("ProjectSetupViewUi", "Remove", 0, QApplication::UnicodeUTF8));
    _btnEventEdit->setText(QApplication::translate("ProjectSetupViewUi", "Rename", 0, QApplication::UnicodeUTF8));
    _btnAddEvent->setText(QApplication::translate("ProjectSetupViewUi", "Add", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ProjectSetupViewUi);
    } // retranslateUi

};

namespace Ui {
    class ProjectSetupViewUi: public Ui_ProjectSetupViewUi {};
} // namespace Ui

#endif // PROJECTSETUPVIEWUI_H
