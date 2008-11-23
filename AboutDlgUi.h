/********************************************************************************
** Form generated from reading ui file 'AboutDlgUi.ui'
**
** Created: Sun Nov 23 00:27:39 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef ABOUTDLGUI_H
#define ABOUTDLGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>

class Ui_AboutDlgUi
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *spacerItem;
    QLabel *m_text;
    QSpacerItem *spacerItem1;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AboutDlgUi)
    {
    if (AboutDlgUi->objectName().isEmpty())
        AboutDlgUi->setObjectName(QString::fromUtf8("AboutDlgUi"));
    QSize size(368, 286);
    size = size.expandedTo(AboutDlgUi->minimumSizeHint());
    AboutDlgUi->resize(size);
    AboutDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    gridLayout = new QGridLayout(AboutDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(AboutDlgUi);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy);
    label->setFrameShape(QFrame::StyledPanel);
    label->setPixmap(QPixmap(QString::fromUtf8(":/images/genesis_med.png")));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem, 0, 1, 1, 1);

    m_text = new QLabel(AboutDlgUi);
    m_text->setObjectName(QString::fromUtf8("m_text"));
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(m_text->sizePolicy().hasHeightForWidth());
    m_text->setSizePolicy(sizePolicy1);
    m_text->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

    gridLayout->addWidget(m_text, 0, 2, 2, 1);

    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem1, 1, 0, 1, 1);

    line = new QFrame(AboutDlgUi);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line, 2, 0, 1, 3);

    buttonBox = new QDialogButtonBox(AboutDlgUi);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);

    gridLayout->addWidget(buttonBox, 3, 0, 1, 3);


    retranslateUi(AboutDlgUi);
    QObject::connect(buttonBox, SIGNAL(accepted()), AboutDlgUi, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), AboutDlgUi, SLOT(reject()));

    QMetaObject::connectSlotsByName(AboutDlgUi);
    } // setupUi

    void retranslateUi(QDialog *AboutDlgUi)
    {
    AboutDlgUi->setWindowTitle(QApplication::translate("AboutDlgUi", "About Ambience", 0, QApplication::UnicodeUTF8));
    label->setText(QString());
    m_text->setText(QApplication::translate("AboutDlgUi", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Genesis Suite</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\">%product_string%</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\">MeiCor Gaming</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px"
        "; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\">Copyright 2008</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><span style=\" font-weight:600;\">Developers:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Corey Derochie</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><span style=\" font-weight:600;\">Third Party"
        ":</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Qt 4.3.0 by Trolltech</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">BASS 2.4 by Un4seen Developments</p></body></html>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AboutDlgUi);
    } // retranslateUi

};

namespace Ui {
    class AboutDlgUi: public Ui_AboutDlgUi {};
} // namespace Ui

#endif // ABOUTDLGUI_H
