/********************************************************************************
** Form generated from reading ui file 'FileSelectionDlgUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef FILESELECTIONDLGUI_H
#define FILESELECTIONDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

class Ui_FileSelectionDlgUi
{
public:
    QGridLayout *gridLayout;
    QListView *m_fileList;
    QPushButton *m_newBtn;
    QDialogButtonBox *buttonBox;
    QSpacerItem *spacerItem;
    QLabel *label;
    QPushButton *m_deleteBtn;

    void setupUi(QDialog *FileSelectionDlgUi)
    {
    if (FileSelectionDlgUi->objectName().isEmpty())
        FileSelectionDlgUi->setObjectName(QString::fromUtf8("FileSelectionDlgUi"));
    QSize size(409, 272);
    size = size.expandedTo(FileSelectionDlgUi->minimumSizeHint());
    FileSelectionDlgUi->resize(size);
    FileSelectionDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    FileSelectionDlgUi->setModal(true);
    gridLayout = new QGridLayout(FileSelectionDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    m_fileList = new QListView(FileSelectionDlgUi);
    m_fileList->setObjectName(QString::fromUtf8("m_fileList"));
    m_fileList->setSelectionMode(QAbstractItemView::MultiSelection);

    gridLayout->addWidget(m_fileList, 1, 0, 1, 4);

    m_newBtn = new QPushButton(FileSelectionDlgUi);
    m_newBtn->setObjectName(QString::fromUtf8("m_newBtn"));

    gridLayout->addWidget(m_newBtn, 2, 0, 1, 1);

    buttonBox = new QDialogButtonBox(FileSelectionDlgUi);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 2, 3, 1, 1);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem, 2, 2, 1, 1);

    label = new QLabel(FileSelectionDlgUi);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 3);

    m_deleteBtn = new QPushButton(FileSelectionDlgUi);
    m_deleteBtn->setObjectName(QString::fromUtf8("m_deleteBtn"));

    gridLayout->addWidget(m_deleteBtn, 2, 1, 1, 1);


    retranslateUi(FileSelectionDlgUi);
    QObject::connect(buttonBox, SIGNAL(accepted()), FileSelectionDlgUi, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), FileSelectionDlgUi, SLOT(reject()));

    QMetaObject::connectSlotsByName(FileSelectionDlgUi);
    } // setupUi

    void retranslateUi(QDialog *FileSelectionDlgUi)
    {
    m_newBtn->setText(QApplication::translate("FileSelectionDlgUi", "New...", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("FileSelectionDlgUi", "Choose files from the following:", 0, QApplication::UnicodeUTF8));
    m_deleteBtn->setText(QApplication::translate("FileSelectionDlgUi", "Delete", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(FileSelectionDlgUi);
    } // retranslateUi

};

namespace Ui {
    class FileSelectionDlgUi: public Ui_FileSelectionDlgUi {};
} // namespace Ui

#endif // FILESELECTIONDLGUI_H
