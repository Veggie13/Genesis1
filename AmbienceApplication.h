#ifndef AMBIENCEAPPLICATION_H
#define AMBIENCEAPPLICATION_H

#include "ExceptionCatchingApplication.h"


class AmbienceApplication : public ExceptionCatchingApplication
{
public:
    AmbienceApplication(int& argc, char** argv);

protected:
    virtual void PerformExceptionAction(const std::exception& ex);

};

#endif
