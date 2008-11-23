#ifndef _BASS_SAMPLE_H_
#define _BASS_SAMPLE_H_

#include "bass_types.h"

namespace BASS
{

    class Channel;

    class Sample
    {
    public:
        ~Sample();

        // Accessors
        Channel* GetChannel(bool onlynew);
        unsigned GetChannels(Channel** chans);
        void     GetData(void* data);
        void     GetInfo(SampleInfo& info);

        // Mutators
        void SetData(void* data);
        void SetInfo(const SampleInfo& info);

        // Control
        void Stop();

    private:
        friend class System;
        Sample(
            unsigned length,
            unsigned freq,
            unsigned chans,
            unsigned max,
            DWORD    flags );
        Sample(
            char*         filename,
            unsigned long offset,
            unsigned      length,
            unsigned      max,
            DWORD         flags );
        Sample(
            void*    memloc,
            unsigned length,
            unsigned max,
            DWORD    flags );

        HSAMPLE m_handle;
        unsigned m_max;
    };

}

#endif
