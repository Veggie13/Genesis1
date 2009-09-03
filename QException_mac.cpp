/*
 ******************************************************************************
 *
 * This code is "borrowed" and modified from code given away freely on the web
 * at http://www.mr-edd.co.uk/?p=66 .
 *
 ******************************************************************************
 */

#include <dlfcn.h>
#include <cxxabi.h>

#include "QException.h"


QException::QException(const QString& msg, int skip)
:   m_msg("")
{
    m_msg = QString("Exception thrown: %1\n").arg(msg);

#if defined(__i386__)
    // Based on code found at:
    // http://www.tlug.org.za/wiki/index.php/Obtaining_a_stack_trace_in_C_upon_SIGSEGV

    Dl_info info;
    void **frame = static_cast<void **>(__builtin_frame_address(0));
    void **bp = static_cast<void **>(*frame);
    void *ip = frame[1];

    bool has_limit = LIMIT != 0;
    unsigned limit = LIMIT;

    while(bp && ip && dladdr(ip, &info))
    {
        if (skip-- > 0)
        {
            if (has_limit && limit-- == 0) break;

            int status = 0;
            char *d = 0;
            QString func = name;
            try { if ((d = abi::__cxa_demangle(info.dli_sname, 0, 0, &status))) func = d; }
            catch(...) {  }
            std::free(d);

            m_msg += QString("    %1    in    %2\n")
                .arg(func)
                .arg(info.dli_fname);

            if(info.dli_sname && QString(info.dli_sname) == "main")) break;
        }

        ip = bp[1];
        bp = static_cast<void**>(bp[0]);
    }

#elif defined(__ppc__)
    // Based on code found at:
    // http://www.informit.com/articles/article.aspx?p=606582&seqNum=4&rl=1

    void *ip = __builtin_return_address(0);
    void **frame = static_cast<void **>(__builtin_frame_address(1));
    bool has_limit = LIMIT != 0;
    unsigned limit = LIMIT;
    Dl_info info;

    do
    {
        if (has_limit && limit-- == 0) break;

        if (dladdr(ip, &info) && skip-- > 0)
        {
            int status = 0;
            char *d = 0;
            QString func = name;
            try { if ((d = abi::__cxa_demangle(info.dli_sname, 0, 0, &status))) func = d; }
            catch(...) {  }
            std::free(d);

            m_msg += QString("    %1    in    %2\n")
                .arg(func)
                .arg(info.dli_fname);
        }

        if (frame && (frame = static_cast<void**>(*frame))) ip = *(frame + 2);
    }
    while (frame && ip);

#else
    // GNU, but neither x86 or PPC
    #error "Sorry but dbg::stack is not supported on this architecture"
#endif

}
