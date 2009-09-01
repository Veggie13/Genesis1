/********************************************************************************
** Form generated from reading ui file 'ExceptionDlgUi.ui'
**
** Created: Mon Aug 31 21:16:31 2009
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef EXCEPTIONDLGUI_H
#define EXCEPTIONDLGUI_H

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
#include <QtGui/QTextEdit>

class Ui_ExceptionDlgUi
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *m_text;
    QSpacerItem *spacerItem;
    QFrame *line;
    QDialogButtonBox *buttonBox;
    QSpacerItem *spacerItem1;
    QTextEdit *m_backtrace;

    void setupUi(QDialog *ExceptionDlgUi)
    {
    if (ExceptionDlgUi->objectName().isEmpty())
        ExceptionDlgUi->setObjectName(QString::fromUtf8("ExceptionDlgUi"));
    QSize size(487, 424);
    size = size.expandedTo(ExceptionDlgUi->minimumSizeHint());
    ExceptionDlgUi->resize(size);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ExceptionDlgUi->sizePolicy().hasHeightForWidth());
    ExceptionDlgUi->setSizePolicy(sizePolicy);
    ExceptionDlgUi->setWindowIcon(QIcon(QString::fromUtf8(":/images/genesis_zoom_ico.png")));
    gridLayout = new QGridLayout(ExceptionDlgUi);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(ExceptionDlgUi);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy1);
    label->setFrameShape(QFrame::StyledPanel);
    label->setPixmap(QPixmap(QString::fromUtf8(":/images/genesis_zoom_ico.png")));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    m_text = new QLabel(ExceptionDlgUi);
    m_text->setObjectName(QString::fromUtf8("m_text"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(m_text->sizePolicy().hasHeightForWidth());
    m_text->setSizePolicy(sizePolicy2);
    m_text->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    m_text->setWordWrap(true);

    gridLayout->addWidget(m_text, 0, 2, 2, 1);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem, 1, 0, 1, 1);

    line = new QFrame(ExceptionDlgUi);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line, 3, 0, 1, 3);

    buttonBox = new QDialogButtonBox(ExceptionDlgUi);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);

    gridLayout->addWidget(buttonBox, 4, 0, 1, 3);

    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem1, 0, 1, 1, 1);

    m_backtrace = new QTextEdit(ExceptionDlgUi);
    m_backtrace->setObjectName(QString::fromUtf8("m_backtrace"));
    QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(m_backtrace->sizePolicy().hasHeightForWidth());
    m_backtrace->setSizePolicy(sizePolicy3);
    m_backtrace->setLineWrapMode(QTextEdit::NoWrap);
    m_backtrace->setReadOnly(true);

    gridLayout->addWidget(m_backtrace, 2, 0, 1, 3);


    retranslateUi(ExceptionDlgUi);
    QObject::connect(buttonBox, SIGNAL(accepted()), ExceptionDlgUi, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), ExceptionDlgUi, SLOT(reject()));

    QMetaObject::connectSlotsByName(ExceptionDlgUi);
    } // setupUi

    void retranslateUi(QDialog *ExceptionDlgUi)
    {
    ExceptionDlgUi->setWindowTitle(QApplication::translate("ExceptionDlgUi", "Unhandled Exception", 0, QApplication::UnicodeUTF8));
    label->setText(QString());
    m_text->setText(QApplication::translate("ExceptionDlgUi", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><span style=\" font-weight:600;\">Ambience has encountered an unhandled exception.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\"><span style=\" font-weight:400;\">Oops. Missed that one. Wow, this is really embarrassing. But really, this </span><span style=\" font-weight:400; font-style:italic;\">is</span><span style=\" font-weight:400;\""
        "> beta software. What did you expect?</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">Could you please send us an email with instructions on how to reproduce the problem, along with the handy message in the box below? That would really help us to fix this problem!</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\">The application will continue, but may be in a damaged state. You should <span style=\" font-style:italic;\">probably</span> save your work and restart it. If you were tryin"
        "g to save when this happened, may your God have mercy on your soul!</p></body></html>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ExceptionDlgUi);
    } // retranslateUi

};

namespace Ui {
    class ExceptionDlgUi: public Ui_ExceptionDlgUi {};
} // namespace Ui

#endif // EXCEPTIONDLGUI_H
