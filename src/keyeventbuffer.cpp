#include "keyeventbuffer.h"

void KeyEventBuffer::processKeyEvent(const KeyEvent& event)
{
    mBuffer.pushBack(event);
}

void KeyEventBuffer::nextKeyEvent(KeyEventStage& next)
{
    if (mBuffer.empty())
    {
        mPrev.nextKeyEvent(next);
    }
    else
    {
        next.processKeyEvent(mBuffer.pop());
    }
}
