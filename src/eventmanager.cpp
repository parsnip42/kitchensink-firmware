#include "eventmanager.h"

#include <elapsedMillis.h>

EventManager::EventManager(Timer&              nTimer,
                           KeySource&          source,
                           KeyEventStage&      input,
                           ToplevelEventStage& toplevel,
                           KeyEventStage&      nDefaultOutput)
    : timer(nTimer)
    , defaultOutput(nDefaultOutput)
    , mSource(source)
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
    mSource.pollKeyEvent(nowMs(), mInput);
}

void EventManager::flush(KeyEventStage& output)
{
    ToplevelEventStage::OutputGuard guard(mToplevel, output);
    
    while (mSource.anyPressed() || !mBuffer.empty())
    {
        mBuffer.pollKeyEvent(mInput);
        timer.pollKeyEvent(mInput);
        mSource.pollKeyEvent(nowMs(), mInput);
    }
}

uint32_t EventManager::nowMs() const
{
    return millis();
}
