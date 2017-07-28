#include "keyeventbuffer.h"

void KeyEventBuffer::pollKeyEvent(KeyEventStage& next)
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
