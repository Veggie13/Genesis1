#ifndef _BASS_PLUGIN_H_
#define _BASS_PLUGIN_H_

#include "bass_types.h"

namespace BASS
{

    class System;

    class Plugin
    {
    public:
        ~Plugin();
        const PluginInfo& GetInfo();

    private:
        friend class System;
        Plugin(char* filename, bool unicodeName);

        HPLUGIN m_handle;
    };

}

#endif
