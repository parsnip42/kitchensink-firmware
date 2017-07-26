#ifndef INCLUDED_EVENTMANAGER_H
#define INCLUDED_EVENTMANAGER_H

#include "keyeventbuffer.h"
#include "keyeventstage.h"
#include "keyeventsource.h"
#include "keyevent.h"
#include "timer.h"

#include <cstdint>

class EventManager
{
public:
    EventManager(KeyEventSource& source,
                 KeyEventBuffer& buffer);

public:
    template <typename EventFunc>
    void poll(const EventFunc& eventFunc);

    Timer::Handle schedule(uint32_t delayMs);
    Timer::Handle scheduleRepeating(uint32_t delayMs);
    void cancel(const Timer::Handle& handle);

private:
    uint32_t nowMs() const;
    
private:
    KeyEventSource&  mSource;
    KeyEventBuffer&  mBuffer;
    Timer            mTimer;
};


inline
EventManager::EventManager(KeyEventSource& source,
                           KeyEventBuffer& buffer)
    : mSource(source)
    , mBuffer(buffer)
    , mTimer(buffer)
{ }

template <typename EventFunc>
void EventManager::poll(const EventFunc& eventFunc)
{
    bool more(true);

    while (more)
    {
        mSource.pollKeyEvent(nowMs());
        mTimer.pollKeyEvent(nowMs());
        
        if (!mBuffer.empty())
        {
            more = eventFunc(mBuffer.pop(), mBuffer);
        }
    }
}

#endif










