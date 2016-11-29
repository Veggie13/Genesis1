#include <QDialog>

#include "ExceptionDlgUi.h"
#include "QException.h"

#include "AmbienceApplication.h"


AmbienceApplication::AmbienceApplication(int& argc, char** argv)
:   ExceptionCatchingApplication(argc, argv)
{
}

void AmbienceApplication::PerformExceptionAction(const std::exception& ex)
{
    QDialog dlg;
    Ui::ExceptionDlgUi* ui = new Ui::ExceptionDlgUi;
    ui->setupUi(&dlg);

    ui->m_backtrace->setPlainText(
        QString("Backtrace follows:\n") +
        QString::fromLocal8Bit(ex.what())
        );

    dlg.exec();
}
