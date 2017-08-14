#ifndef INCLUDED_EVENTSERIALIZER_H
#define INCLUDED_EVENTSERIALIZER_H

#include "types/strbuf.h"
#include "types/strref.h"
#include "data/keycodes.h"
#include "types/strostream.h"

class Event;

namespace EventSerializer
{

void serialize(const Event& event, const StrOStream& os);
void deserialize(const StrRef& eventStr, Event& event);

};

#endif
