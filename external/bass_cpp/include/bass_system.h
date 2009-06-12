#ifndef _BASS_SYSTEM_H_
#define _BASS_SYSTEM_H_

#include <string>

#include "bass_types.h"


namespace BASS
{

    class IDirectSound;
    class IDirectSound3DListener;
    class Plugin;
    class Sample;
    class Stream;

    class System
    {
    public:
        ~System();

        static System& Get();
        static void    Free();
        static DWORD   GetVersion();
        static bool    MajorVersionMatches();

        void Init(int dev, DWORD rate, DWORD flags, HWND win=0, GUID* clsid=NULL);

        // Accessors
        Algorithm3D             Get3DAlgorithm();
        unsigned                GetBufferLength();
        float                   GetCPU();
        DeviceId                GetDevice();
        void                    GetDeviceInfo(DeviceId device, DeviceInfo& devInfo);
        unsigned                GetFileFormatVerificationLength();
        unsigned                GetGlobalMusicVolume();
        unsigned                GetGlobalSampleVolume();
        unsigned                GetGlobalStreamVolume();
        IDirectSound*           GetIDirectSound();
        IDirectSound3DListener* GetIDirectSound3DListener();
        void                    GetInfo(Info& info);
        unsigned                GetMaxVirtualChannels();
        std::string             GetNetAgentHeader();
        unsigned                GetNetBufferLength();
        unsigned                GetNetConnectionTimeout();
        unsigned                GetNetPrebufferAmount();
        std::string             GetNetProxySettings();
        unsigned                GetNumUpdateThreads();
        unsigned                GetRecBufferLength();
        unsigned                GetUpdatePeriod();
        float                   GetVolume();
        CurveStyle              GetPanningCurve();
        CurveStyle              GetVolumeCurve();
        bool                    PlayAllowedWhenPaused();
        bool                    ProcessingPlaylistUrls();
        bool                    UsingFloatForDSP();
        bool                    UsingPassiveFtp();

        // Mutators
        void AllowPlayWhenPaused(bool allow);
        void Set3DAlgorithm(Algorithm3D algo);
        void SetBufferLength(unsigned length);
        void SetDevice(DeviceId dev);
        void SetFileFormatVerificationLength(unsigned length);
        void SetGlobalMusicVolume(unsigned vol);
        void SetGlobalSampleVolume(unsigned vol);
        void SetGlobalStreamVolume(unsigned vol);
        void SetMaxVirtualChannels(unsigned numVirt);
        void SetNetAgentHeader(const std::string& header);
        void SetNetBufferLength(unsigned length);
        void SetNewConnectionTimeout(unsigned to);
        void SetNetPrebufferAmount(unsigned prebuf);
        void SetNetProxySettings(const std::string& settings);
        void SetNumUpdateThreads(unsigned numThreads);
        void SetRecBufferLength(unsigned length);
        void SetUpdatePeriod(unsigned period);
        void SetVolume(float vol);
        void SetPanningCurve(CurveStyle style);
        void SetVolumeCurve(CurveStyle style);
        void ProcessPlaylistUrls(bool process);
        void UseFloatForDSP(bool use);
        void UsePassiveFtp(bool use);

        // Control
        void Pause();
        void Start();
        void Stop();
        void Update(unsigned length);

        // Plugins
        Plugin* LoadPlugin(char* filename, bool unicodeName=false);

        // 3D & EAX
        void Apply3D();
        void Get3DFactors(float* distf, float* rollf, float* doppf);
        void Get3DPosition(
                Vector3D* pos,
                Vector3D* vel,
                Vector3D* front,
                Vector3D* top );
        void GetEAXParameters(
                EaxEnvironment* env,
                float* vol,
                float* decay,
                float* damp );
        void Set3DFactors(float distf, float rollf, float doppf);
        void Set3DPosition(
                Vector3D* pos,
                Vector3D* vel,
                Vector3D* front,
                Vector3D* top );
        void SetEAXParameters(
                EaxEnvironment env,
                float vol,
                float decay,
                float damp );

        // Samples
        Sample* CreateSample(
                    unsigned length,
                    unsigned freq,
                    unsigned chans,
                    unsigned max,
                    DWORD    flags );
        Sample* LoadSampleFromFile(
                    char*         filename,
                    unsigned long offset,
                    unsigned      length,
                    unsigned      max,
                    DWORD         flags );
        Sample* LoadSampleFromMemory(
                    void*    memloc,
                    unsigned length,
                    unsigned max,
                    DWORD    flags );

        // Streams
        Stream* CreateStream(
                    unsigned         freq,
                    unsigned         chans,
                    DWORD            flags,
                    StreamProcedure* proc,
                    void*            user );
        Stream* LoadStreamFromFile(
                    char*         file,
                    unsigned long offset,
                    unsigned long length,
                    DWORD         flags );
        Stream* LoadStreamFromMemory(
                    void*         memloc,
                    unsigned long length,
                    DWORD         flags );
        Stream* LoadStreamUsingUser(
                    DWORD           system,
                    DWORD           flags,
                    FileProcedures* procs,
                    void*           user );
        Stream* LoadStreamFromUrl(
                    char*              url,
                    unsigned           offset,
                    DWORD              flags,
                    DownloadProcedure* proc,
                    void*              user );

    private:
        System(); // private constructor for the singleton

        static System* instance; // singleton
    };

}

#endif
