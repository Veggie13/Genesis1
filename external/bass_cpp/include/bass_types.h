#ifndef _BASS_TYPES_H_
#define _BASS_TYPES_H_

#include <bass.h>

namespace BASS
{

    typedef BASS_CHANNELINFO    ChannelInfo;
    typedef BASS_DEVICEINFO     DeviceInfo;
    typedef BASS_INFO           Info;
    typedef BASS_PLUGININFO     PluginInfo;
    typedef BASS_SAMPLE         SampleInfo;
    typedef BASS_3DVECTOR       Vector3D;

    typedef DWORD               Algorithm3D;
    typedef DWORD               DeviceId;
    typedef DWORD               EaxEnvironment;

    typedef HDSP                DspHandle;
    typedef HFX                 EffectHandle;
    typedef HSYNC               SyncHandle;

    typedef DOWNLOADPROC        DownloadProcedure;
    typedef DSPPROC             DspProcedure;
    typedef BASS_FILEPROCS      FileProcedures;
    typedef STREAMPROC          StreamProcedure;
    typedef SYNCPROC            SyncProcedure;

    enum CurveStyle {LINEAR, LOG};
    enum ChannelState {
            STOPPED = BASS_ACTIVE_STOPPED,
            PLAYING = BASS_ACTIVE_PLAYING,
            PAUSED  = BASS_ACTIVE_PAUSED,
            STALLED = BASS_ACTIVE_STALLED };

}

#endif
