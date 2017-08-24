#ifndef INCLUDED_EVENTBUFFER_H
#define INCLUDED_EVENTBUFFER_H

#include "event/eventstage.h"
#include "event/event.h"
#include "types/circularbuffer.h"

class EventBuffer : public EventStage
{
public:
    EventBuffer() = default;

public:
    virtual void processEvent(const Event& event) override;
    
    void pollEvent(EventStage& next);

public:
    bool empty() const;
    Event pop();

private:
    CircularBuffer<Event, 48> mBuffer;
};


inline
bool EventBuffer::empty() const
{
    return mBuffer.empty();
}

inline
Event EventBuffer::pop()
{
    return mBuffer.pop();
}


#endif
