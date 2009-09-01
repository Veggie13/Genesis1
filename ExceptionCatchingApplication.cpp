#include "ExceptionCatchingApplication.h"


ExceptionCatchingApplication::ExceptionCatchingApplication(int& argc, char** argv)
:   QApplication(argc, argv)
{
}

bool ExceptionCatchingApplication::notify(QObject *receiver, QEvent *e)
{
    try
    {
        return QApplication::notify(receiver, e);
    }
    catch (const std::exception& ex)
    {
        PerformExceptionAction(ex);
    }
    catch (...)
    {
        PerformExceptionAction(std::exception());
    }

    return true;
}

