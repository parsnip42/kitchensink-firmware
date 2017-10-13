#include "eventmanager.h"

#include "event/eventsource.h"

EventManager::EventManager(TimerManager&       nTimer,
                           EventSource&        eventSource,
                           LedSource&          ledSource,
                           EventStage&         input,
                           ToplevelEventStage& toplevel,
                           EventStage&         nDefaultOutput)
    : timer(nTimer)
    , defaultOutput(nDefaultOutput)
    , mEventSource(eventSource)
    , mLedSource(ledSource)
    , mInput(input)
    , mToplevel(toplevel)
{ }

bool EventManager::processEvent(const Event& event)
{
    return mBuffer.processEvent(event);
}

void EventManager::poll(EventStage& output)
{
    ToplevelEventStage::OutputGuard guard(mToplevel, output);
        
    mBuffer.pollEvent(mInput);
    timer.pollEvent(mInput);
    mEventSource.pollEvent(mInput);
    mLedSource.pollEvent(mInput);
}

void EventManager::flush(EventStage& output)
{
    ToplevelEventStage::OutputGuard guard(mToplevel, output);
    
    while (mEventSource.flushEvents(mInput))
    {
        timer.pollEvent(mInput);
        mLedSource.pollEvent(mInput);
    }
}
