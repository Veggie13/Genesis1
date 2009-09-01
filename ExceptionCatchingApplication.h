#ifndef EXCEPTIONCATCHINGAPPLICATION_H
#define EXCEPTIONCATCHINGAPPLICATION_H

#include <QApplication>


class ExceptionCatchingApplication : public QApplication
{
public:
    ExceptionCatchingApplication(int& argc, char** argv);
    virtual bool notify(QObject *receiver, QEvent *e);

protected:
    virtual void PerformExceptionAction(const std::exception& ex) = 0;
};

#endif
