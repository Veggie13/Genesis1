#ifndef _BASS_EXCEPTION_H_
#define _BASS_EXCEPTION_H_

#include <exception>
#include <string>

namespace BASS
{

    class Exception : public std::exception
    {
    public:
        static void ThrowError();

        virtual ~Exception() throw();

        virtual const char* what();

    private:
        Exception(const char* msg);

        std::string m_msg;
    };

}

#define BASS_ASSERT(x)                  \
    if ( !(x) )                         \
    {                                   \
        BASS::Exception::ThrowError();  \
    }

#endif
