#ifndef INCLUDED_EVENTMANAGER_H
#define INCLUDED_EVENTMANAGER_H

#include "keyeventbuffer.h"
#include "keyeventstage.h"
#include "keyeventsource.h"
#include "keyevent.h"
#include "keyprocessor.h"
#include "timer.h"

#include <cstdint>

class EventManager
{
public:
    EventManager(Timer&          nTimer,
                 KeyProcessor  & source,
                 KeyEventBuffer& buffer,
                 KeyEventStage&  input,
                 KeyEventStage&  output);

public:
    template <typename EventFunc>
    void poll(const EventFunc& eventFunc);

    void pollStage(KeyEventStage& output);

    void cancel(const Timer::Handle& handle);
    
    KeyEventStage& buffer()
    {
        return mBuffer;
    }

    KeyEventStage& output()
    {
        return mOutput;
    }

public:
    Timer& timer;
    KeyProcessor&   mSource;
    
private:
    uint32_t nowMs() const;
    
private:
    KeyEventBuffer& mBuffer;
    KeyEventStage&  mInput;
    KeyEventStage&  mOutput;
};


inline
EventManager::EventManager(Timer&          nTimer,
                           KeyProcessor&   source,
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
inline
void EventManager::poll(const EventFunc& eventFunc)
{
    bool more(true);
    
    mSource.releaseAll(mInput);
    
    while (more)
    {
        mSource.pollKeyEvent(nowMs(), mInput);
        timer.pollKeyEvent(nowMs(), mInput);
        
        if (!mBuffer.empty())
        {
            more = eventFunc(mBuffer.pop(), mBuffer);
        }
    }

    mSource.pressAll(mInput);
}

inline
void EventManager::pollStage(KeyEventStage& output)
{
    mSource.pollKeyEvent(nowMs(), mInput);
    timer.pollKeyEvent(nowMs(), mInput);
    
    if (!mBuffer.empty())
    {
        output.processKeyEvent(mBuffer.pop());
    }
}

#endif








