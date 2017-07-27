#include "eventmanager.h"

#include <elapsedMillis.h>

EventManager::EventManager(Timer&              nTimer,
                           KeyProcessor&       source,
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
    auto now(nowMs());

    ToplevelEventStage::OutputGuard guard(mToplevel, output);
        
    mBuffer.pollKeyEvent(now, mInput);
    timer.pollKeyEvent(now, mInput);
    mSource.pollKeyEvent(now, mInput);
}

uint32_t EventManager::nowMs() const
{
    return millis();
}
