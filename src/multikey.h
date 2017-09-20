#ifndef INCLUDED_MULTIKEY_H
#define INCLUDED_MULTIKEY_H

#include "event/event.h"
#include "types/strbuf.h"
#include "config.h"

#include <array>

class EventStage;

class MultiKey
{
private:
public:
    typedef std::array<Event, Config::kMultiKeyTapCount> Events;
    
public:
    MultiKey();
    
public:
    Event event(int taps);

    void press();
    void release(EventStage& next);
    bool trigger(EventStage& next);

public:
    StrBuf<Config::kMultiKeyNameLen> name;
    Events                           events;

private:
    uint8_t mTaps;
    Event   mActiveEvent;
    bool    mReleased;
    bool    mTriggered;
};


inline
MultiKey::MultiKey()
    : mTaps(0)
    , mReleased(false)
    , mTriggered(false)
{ }

inline
Event MultiKey::event(int taps)
{
    std::size_t index(taps - 1);
    
    if (index < events.size())
    {
        return events[index];
    }

    return Event();
}

#endif
