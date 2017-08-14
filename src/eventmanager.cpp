#include "eventmanager.h"

#include <elapsedMillis.h>

EventManager::EventManager(Timer&              nTimer,
                           KeySource&          keySource,
                           LedSource&          ledSource,
                           EventStage&         input,
                           ToplevelEventStage& toplevel,
                           EventStage&         nDefaultOutput)
    : timer(nTimer)
    , defaultOutput(nDefaultOutput)
    , mKeySource(keySource)
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
    mKeySource.pollEvent(nowMs(), mInput);
    mLedSource.pollEvent(mInput);
}

void EventManager::flush(EventStage& output)
{
    ToplevelEventStage::OutputGuard guard(mToplevel, output);
    
    while (mKeySource.anyPressed() || !mBuffer.empty())
    {
        mBuffer.pollEvent(mInput);
        timer.pollEvent(mInput);
        mKeySource.pollEvent(nowMs(), mInput);
        mLedSource.pollEvent(mInput);
    }
}

uint32_t EventManager::nowMs() const
{
    return millis();
}
