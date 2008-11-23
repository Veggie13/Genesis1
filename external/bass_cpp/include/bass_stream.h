#ifndef _BASS_STREAM_H_
#define _BASS_STREAM_H_

#include "bass_channel.h"

namespace BASS
{

    class Stream : public Channel
    {
    public:
        virtual ~Stream();

        unsigned long   GetFilePosition(DWORD mode);
        unsigned        PutData(void* buffer, unsigned length);
        unsigned        PutFileData(void* buffer, unsigned length);

    private:
        friend class System;
        Stream(
            unsigned         freq,
            unsigned         chans,
            DWORD            flags,
            StreamProcedure* proc,
            void*            user );
        Stream(
            char*         file,
            unsigned long offset,
            unsigned long length,
            DWORD         flags );
        Stream(
            void*         memloc,
            unsigned long length,
            DWORD         flags );
        Stream(
            DWORD           system,
            DWORD           flags,
            FileProcedures* procs,
            void*           user );
        Stream(
            char*              url,
            unsigned           offset,
            DWORD              flags,
            DownloadProcedure* proc,
            void*              user );
    };

}

#endif
