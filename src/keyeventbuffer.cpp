#include "keyeventbuffer.h"

void KeyEventBuffer::pollKeyEvent(uint32_t timeMs, KeyEventStage& next)
{
    if (!mBuffer.empty())
    {
        next.processKeyEvent(mBuffer.pop());
    }
}

void KeyEventBuffer::processKeyEvent(const KeyEvent& event)
{
    mBuffer.pushBack(event);
}
