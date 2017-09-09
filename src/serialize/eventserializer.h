#ifndef INCLUDED_EVENTSERIALIZER_H
#define INCLUDED_EVENTSERIALIZER_H

#include "types/strbuf.h"
#include "types/strref.h"
#include "types/stroutstream.h"

class Event;

namespace EventSerializer
{

void serialize(const Event& event, const StrOutStream& os);
void deserialize(const StrRef& eventStr, Event& event);

void serializeReadable(const Event& event, const StrOutStream& os);

};

#endif
