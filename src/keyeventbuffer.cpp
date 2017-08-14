#include "keyeventbuffer.h"

void EventBuffer::pollEvent(EventStage& next)
{
    if (!mBuffer.empty())
    {
        next.processEvent(mBuffer.pop());
    }
}

void EventBuffer::processEvent(const Event& event)
{
    mBuffer.pushBack(event);
}
