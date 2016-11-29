#pragma once

#include "ASessionEvent.h"


class NoteEvent : public ASessionEvent
{
public:
    DECLARE_STANDARD_EVENT_FACTORY( NoteEvent )

    NoteEvent( const QString& note );
    NoteEvent( const IDeserializer* source )
        : ASessionEvent(source) { Deserialize(source); }

    virtual EventTypeId Type() const { return ID; }
    virtual int IntData() const { return 0; }
    virtual bool BoolData() const { return false; }
    virtual QString StringData() const { return _note; }

    virtual void Serialize( ISerializer* dest ) const;

protected:
    virtual void Deserialize( const IDeserializer* source );

private:
    QString _note;

};
