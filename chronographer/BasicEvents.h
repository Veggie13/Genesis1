#pragma once

#include "ASessionEvent.h"


#define DeclareBasicEvent(Name) \
    class Name##Event : public ASessionEvent { public:                          \
        DECLARE_STANDARD_EVENT_FACTORY( Name##Event )                           \
        Name##Event(): ASessionEvent(NULL, NULL, NULL) { }                      \
        Name##Event(const IDeserializer* source)                                \
            : ASessionEvent(source) { }                                         \
        virtual EventTypeId Type() const { return ID; }                         \
        virtual int IntData() const { return 0; }                               \
        virtual bool BoolData() const { return false; }                         \
        virtual QString StringData() const { return #Name; } }

#define DefineBasicEvent(Name) DEFINE_STANDARD_EVENT_FACTORY( Name##Event )

DeclareBasicEvent( Start );
DeclareBasicEvent( End );
DeclareBasicEvent( PauseToggle );
