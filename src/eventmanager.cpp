#include "eventmanager.h"

EventManager::EventManager(Timer&              nTimer,
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

void EventManager::processEvent(const Event& event)
{
    mBuffer.processEvent(event);
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
    
    while (keySource.anyPressed() || !mBuffer.empty())
    {
        mBuffer.pollEvent(mInput);
        timer.pollEvent(mInput);
        keySource.pollEvent(mInput);
        mLedSource.pollEvent(mInput);
    }
}
