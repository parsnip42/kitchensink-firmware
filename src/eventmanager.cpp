#include "eventmanager.h"

#include <elapsedMillis.h>

EventManager::EventManager(Timer&              nTimer,
                           KeySource&          keySource,
                           LedSource&          ledSource,
                           KeyEventStage&      input,
                           ToplevelEventStage& toplevel,
                           KeyEventStage&      nDefaultOutput)
    : timer(nTimer)
    , defaultOutput(nDefaultOutput)
    , mKeySource(keySource)
    , mLedSource(ledSource)
    , mInput(input)
    , mToplevel(toplevel)
{ }

void EventManager::processKeyEvent(const KeyEvent& event)
{
    mBuffer.processKeyEvent(event);
}

void EventManager::poll(KeyEventStage& output)
{
    ToplevelEventStage::OutputGuard guard(mToplevel, output);
        
    mBuffer.pollKeyEvent(mInput);
    timer.pollKeyEvent(mInput);
    mKeySource.pollKeyEvent(nowMs(), mInput);
    mLedSource.pollKeyEvent(mInput);
}

void EventManager::flush(KeyEventStage& output)
{
    ToplevelEventStage::OutputGuard guard(mToplevel, output);
    
    while (mKeySource.anyPressed() || !mBuffer.empty())
    {
        mBuffer.pollKeyEvent(mInput);
        timer.pollKeyEvent(mInput);
        mKeySource.pollKeyEvent(nowMs(), mInput);
        mLedSource.pollKeyEvent(mInput);
    }
}

uint32_t EventManager::nowMs() const
{
    return millis();
}
