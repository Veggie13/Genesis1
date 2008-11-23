#ifndef _BASS_CHANNEL_H_
#define _BASS_CHANNEL_H_

#include "bass_types.h"

namespace BASS
{

    class DspFunction;
    class Effect;
    class Synchronizer;

    class Channel
    {
    public:
        virtual ~Channel();

        // Utilities
        double          Bytes2Seconds(unsigned long pos);
        unsigned long   Seconds2Bytes(double pos);
        DWORD           Flags(DWORD flags, DWORD mask);

        // Accessors
        void            Get3DAttributes(
                            DWORD* mode,
                            float* min,
                            float* max,
                            DWORD* iangle,
                            DWORD* oangle,
                            float* outvol );
        void            Get3DPosition(
                            Vector3D* pos,
                            Vector3D* orient,
                            Vector3D* vel );
        void            GetAttribute(DWORD attrib, float* value);
        void            GetData(void* buffer, DWORD length);
        DeviceId        GetDevice();
        void            GetInfo(ChannelInfo& info);
        unsigned long   GetLength(bool useOrders=false);
        DWORD           GetLevel();
        unsigned long   GetPosition(bool useOrders=false);
        const char*     GetTags(DWORD tags);
        ChannelState    GetActiveState();
        bool            AttributeIsSliding(DWORD attrib);

        // Mutators
        void            Set3DAttributes(
                            int mode,
                            float min,
                            float max,
                            int iangle,
                            int oangle,
                            float outvol );
        void            Set3DPosition(
                            Vector3D* pos,
                            Vector3D* orient,
                            Vector3D* vel );
        void            SetAttribute(DWORD attrib, float value);
        void            SetDevice(DeviceId dev);
        DspHandle       SetDSP(DspProcedure* dsp, void* user, int priority);
        EffectHandle    SetEffect(DWORD type, int priority);
        void            SetLink(Channel* chan);
        void            SetPosition(unsigned long pos, DWORD mode);
        SyncHandle      SetSync(DWORD type, QWORD param, SyncProcedure* proc, void* user);
        void            SlideAttribute(DWORD attrib, float value, unsigned time);

        // Control
        void            Lock();
        void            UnLock();
        void            Pause();
        void            Play(bool restart=false);
        void            Stop();
        void            Update(unsigned length);

        // Removal
        void            RemoveDSP(DspHandle dsp);
        void            RemoveEffect(EffectHandle fx);
        void            RemoveLink(Channel* chan);
        void            RemoveSync(SyncHandle sync);

    protected:
        friend class Sample;
        Channel(DWORD handle);

        DWORD m_handle;

    };

}

#endif
