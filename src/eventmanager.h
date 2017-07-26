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
    EventManager(Timer&          nTimer,
                 KeyEventSource& source,
                 KeyEventBuffer& buffer,
                 KeyEventStage&  input,
                 KeyEventStage&  output);

public:
    template <typename EventFunc>
    void poll(const EventFunc& eventFunc);

    void cancel(const Timer::Handle& handle);
    
    KeyEventStage& output()
    {
        return mOutput;
    }
public:
    Timer& timer;
    
private:
    uint32_t nowMs() const;
    
private:
    KeyEventSource& mSource;
    KeyEventBuffer& mBuffer;
    KeyEventStage&  mInput;
    KeyEventStage&  mOutput;
};


inline
EventManager::EventManager(Timer&          nTimer,
                           KeyEventSource& source,
                           KeyEventBuffer& buffer,
                           KeyEventStage&  input,
                           KeyEventStage&  output)
    : timer(nTimer)
    , mSource(source)
    , mBuffer(buffer)
    , mInput(input)
    , mOutput(output)
{ }

template <typename EventFunc>
void EventManager::poll(const EventFunc& eventFunc)
{
    bool more(true);

    while (more)
    {
        mSource.pollKeyEvent(nowMs(), mInput);
        timer.pollKeyEvent(nowMs(), mInput);
        
        if (!mBuffer.empty())
        {
            more = eventFunc(mBuffer.pop(), mBuffer);
        }
    }
}

#endif










