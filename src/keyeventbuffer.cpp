#include "keyeventbuffer.h"

void EventBuffer::pollEvent(EventStage& next)
{
    if (!mBuffer.empty())
    {
        next.processEvent(mBuffer.pop());
    }
}

bool EventBuffer::processEvent(const Event& event)
{
    mBuffer.pushBack(event);

    return true;
}
