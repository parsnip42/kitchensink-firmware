#include "eventmanager.h"

#include "event/eventsource.h"

EventManager::EventManager(TimerManager&       nTimerManager,
                           EventSource&        eventSource,
                           EventStage&         input,
                           ToplevelEventStage& toplevel,
                           EventStage&         nDefaultOutput)
    : timerManager(nTimerManager)
    , defaultOutput(nDefaultOutput)
    , mEventSource(eventSource)
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
    timerManager.pollEvent(mInput);
    mEventSource.pollEvent(mInput);
}

void EventManager::flush(EventStage& output)
{
    ToplevelEventStage::OutputGuard guard(mToplevel, output);
    
    while (mEventSource.flushEvents(mInput))
    {
        timerManager.pollEvent(mInput);
    }
}
