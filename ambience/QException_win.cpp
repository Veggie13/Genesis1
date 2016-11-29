/*
 ******************************************************************************
 *
 * This code is "borrowed" and modified from code given away freely on the web
 * at http://www.mr-edd.co.uk/?p=66 .
 *
 ******************************************************************************
 */

#include <windows.h>
#include <imagehlp.h>
#include <bfd.h> // link against libbfd and libiberty
#include <psapi.h> // link against psapi
#include <cxxabi.h>

#include "QException.h"


struct find_data
{
    QString func;
    asymbol **symbol_table;
    bfd_vma counter;
};

void find_function_name_in_section(bfd *abfd, asection *sec, void *opaque_data)
{
    assert(sec);
    assert(opaque_data);
    find_data &data = *static_cast<find_data *>(opaque_data);

    if (!data.func.isEmpty()) return; // already found it

    if (!(bfd_get_section_flags(abfd, sec) & SEC_ALLOC)) return;

    bfd_vma vma = bfd_get_section_vma(abfd, sec);
    if (data.counter < vma || vma + bfd_get_section_size(sec) <= data.counter) return;

    const char *func = 0;
    const char *file = 0;
    unsigned line = 0;

    if (bfd_find_nearest_line(abfd, sec, data.symbol_table, data.counter - vma, &file, &func, &line) && func)
    {
        int status = 0;
        char *d = 0;
        data.func = func;
        try { if ((d = abi::__cxa_demangle(func, 0, 0, &status))) data.func = d; }
        catch(...) {  }
        std::free(d);
    }
}

QException::QException(const QString& msg, int skip)
:   m_msg("")
{
    m_msg = QString("Exception thrown: %1\n").arg(msg);

    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);
    EnterCriticalSection(&cs);

    bfd *abfd = 0;
    asymbol **symbol_table = 0;

    char procname[MAX_PATH];
    GetModuleFileNameEx(GetCurrentProcess(), NULL, procname, sizeof procname);

    bfd_init();
    abfd = bfd_openr(procname, 0);
    if (!abfd)
    {
        m_msg = "Failed to parse object data for the executable";
        return;
    }

    char **formats = 0;
    bool b1 = bfd_check_format(abfd, bfd_object);
    bool b2 = bfd_check_format_matches(abfd, bfd_object, &formats);
    bool b3 = bfd_get_file_flags(abfd) & HAS_SYMS;

    if (!(b1 && b2 && b3))
    {
        bfd_close(abfd);
        free(formats);
        m_msg = "Failed to parse object data for the executable";
        return;
    }
    free(formats);

    // Load symbol table
    unsigned dummy = 0;
    if (bfd_read_minisymbols(abfd, FALSE, (void **)&symbol_table, &dummy) == 0 &&
        bfd_read_minisymbols(abfd, TRUE, (void **)&symbol_table, &dummy) < 0)
    {
        free(symbol_table);
        bfd_close(abfd);
        m_msg = "Failed to parse object data for the executable";
        return;
    }

    SymInitialize(GetCurrentProcess(), 0, true);

    STACKFRAME frame; std::memset(&frame, 0, sizeof frame);
    CONTEXT context;  std::memset(&context, 0, sizeof(CONTEXT));
    context.ContextFlags = CONTEXT_FULL;

    HMODULE lib = LoadLibrary("kernel32.dll");
    if (!lib)
    {
        m_msg = "Cannot show backtrace. Failed to load kernel32.dll.";
        return;
    }

    FARPROC proc = GetProcAddress(lib, "RtlCaptureContext");
    if (!proc)
    {
        m_msg = "Cannot show backtrace. "
                "Failed to load function RtlCaptureContext "
                "from library kernel32.dll.";
        return;
    }

    void (WINAPI *RtlCaptureContext_) (CONTEXT*) =
        reinterpret_cast<void (WINAPI *) (CONTEXT*)>(proc);

    RtlCaptureContext_(&context);

    frame.AddrPC.Offset = context.Eip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context.Esp;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context.Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;

    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();

    bool has_limit = LIMIT != 0;
    char symbol_buffer[sizeof(IMAGEHLP_SYMBOL) + 255];
    char module_name_raw[MAX_PATH];

    unsigned limit = LIMIT;
    while(StackWalk(IMAGE_FILE_MACHINE_I386, process, thread,
                    &frame, &context, 0, SymFunctionTableAccess, SymGetModuleBase, 0    ))
    {
        if (skip-- > 0)
            continue;

        if (has_limit && limit-- == 0) break;

        IMAGEHLP_SYMBOL *symbol = reinterpret_cast<IMAGEHLP_SYMBOL *>(symbol_buffer);
        symbol->SizeOfStruct = (sizeof *symbol) + 255;
        symbol->MaxNameLength = 254;

        DWORD module_base = SymGetModuleBase(process, frame.AddrPC.Offset);
        QString module_name = "[unknown module]";
        if(   module_base && GetModuleFileName(reinterpret_cast<HINSTANCE>(module_base), module_name_raw, MAX_PATH))
            module_name = module_name_raw;

        find_data data;
        data.symbol_table = symbol_table;
        data.counter = frame.AddrPC.Offset;

        bfd_map_over_sections(abfd, &find_function_name_in_section, &data);
        QString func = data.func;

        if (func.isEmpty())
        {
            DWORD displacement = 0; // dummy variable
            BOOL got_symbol =
                SymGetSymFromAddr(process, frame.AddrPC.Offset, &displacement, symbol);
            func = got_symbol ?
                QString::fromLocal8Bit(symbol->Name) : "[unknown function]";
        }

        m_msg += QString("    %1    in    %2\n")
            .arg(func)
            .arg(module_name);
    }

    SymCleanup(GetCurrentProcess());

    LeaveCriticalSection(&cs);
    DeleteCriticalSection(&cs);

    free(symbol_table);
    bfd_close(abfd);
}
