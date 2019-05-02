#include "event/eventlogger.h"

#include "log/log.h"
#include "serialize/eventserializer.h"

void EventLogger::logEvent(const Event& event)
{
    StrBuf<12> out;
    StrOutStream oss(out);

    EventSerializer::serializeReadable(event, oss);
    
    KS_LOG(out);
}

bool EventLogger::processEvent(const Event& event)
{
    logEvent(event);
    mNext.processEvent(event);

    return true;
}

