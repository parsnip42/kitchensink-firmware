#include "eventmanager.h"

EventManager::EventManager(TimerManager&              nTimer,
                           KeySource&          nKeySource,
                           LedSource&          ledSource,
                           EventStage&         input,
                           ToplevelEventStage& toplevel,
                           EventStage&         nDefaultOutput)
    : timer(nTimer)
    , keySource(nKeySource)
    , defaultOutput(nDefaultOutput)
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
    keySource.pollEvent(mInput);
    mLedSource.pollEvent(mInput);
}

void EventManager::flush(EventStage& output)
{
    ToplevelEventStage::OutputGuard guard(mToplevel, output);
    
    while (keySource.anyPressed())
    {
        timer.pollEvent(mInput);
        keySource.pollEvent(mInput);
        mLedSource.pollEvent(mInput);
    }
}
