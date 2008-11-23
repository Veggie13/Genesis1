/********************************************************************************
** Form generated from reading ui file 'OpenOptionsDlgUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef OPENOPTIONSDLGUI_H
#define OPENOPTIONSDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

class Ui_OpenOptionsDlgUi
{
public:
    QVBoxLayout *vboxLayout;
    QListWidget *m_recentList;
    QPushButton *m_openRecentBtn;
    QPushButton *m_openOtherBtn;
    QPushButton *m_newProjectBtn;

    void setupUi(QDialog *OpenOptionsDlgUi)
    {
    if (OpenOptionsDlgUi->objectName().isEmpty())
        OpenOptionsDlgUi->setObjectName(QString::fromUtf8("OpenOptionsDlgUi"));
    OpenOptionsDlgUi->setWindowModality(Qt::WindowModal);
    QSize size(279, 304);
    size = size.expandedTo(OpenOptionsDlgUi->minimumSizeHint());
    OpenOptionsDlgUi->resize(size);
    OpenOptionsDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    vboxLayout = new QVBoxLayout(OpenOptionsDlgUi);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    m_recentList = new QListWidget(OpenOptionsDlgUi);
    m_recentList->setObjectName(QString::fromUtf8("m_recentList"));
    m_recentList->setSelectionBehavior(QAbstractItemView::SelectRows);

    vboxLayout->addWidget(m_recentList);

    m_openRecentBtn = new QPushButton(OpenOptionsDlgUi);
    m_openRecentBtn->setObjectName(QString::fromUtf8("m_openRecentBtn"));

    vboxLayout->addWidget(m_openRecentBtn);

    m_openOtherBtn = new QPushButton(OpenOptionsDlgUi);
    m_openOtherBtn->setObjectName(QString::fromUtf8("m_openOtherBtn"));

    vboxLayout->addWidget(m_openOtherBtn);

    m_newProjectBtn = new QPushButton(OpenOptionsDlgUi);
    m_newProjectBtn->setObjectName(QString::fromUtf8("m_newProjectBtn"));

    vboxLayout->addWidget(m_newProjectBtn);


    retranslateUi(OpenOptionsDlgUi);

    QMetaObject::connectSlotsByName(OpenOptionsDlgUi);
    } // setupUi

    void retranslateUi(QDialog *OpenOptionsDlgUi)
    {
    OpenOptionsDlgUi->setWindowTitle(QApplication::translate("OpenOptionsDlgUi", "Startup Options", 0, QApplication::UnicodeUTF8));
    m_openRecentBtn->setText(QApplication::translate("OpenOptionsDlgUi", "Open Recent", 0, QApplication::UnicodeUTF8));
    m_openOtherBtn->setText(QApplication::translate("OpenOptionsDlgUi", "Open Other...", 0, QApplication::UnicodeUTF8));
    m_newProjectBtn->setText(QApplication::translate("OpenOptionsDlgUi", "New Project", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(OpenOptionsDlgUi);
    } // retranslateUi

};

namespace Ui {
    class OpenOptionsDlgUi: public Ui_OpenOptionsDlgUi {};
} // namespace Ui

#endif // OPENOPTIONSDLGUI_H
