#include "IDeserializer.h"
#include "ISerializer.h"

#include "NoteEvent.h"


DEFINE_STANDARD_EVENT_FACTORY( NoteEvent )

NoteEvent::NoteEvent( const QString& note )
:   ASessionEvent(NULL, NULL, NULL),
    _note(note)
{ }

void NoteEvent::Serialize( ISerializer* dest ) const
{
    dest->Serialize( "note", _note );
}

void NoteEvent::Deserialize( const IDeserializer* source )
{
    source->Deserialize( "note", _note );
}
