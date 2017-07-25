#ifndef INCLUDED_KEYEVENTPIPELINE_H
#define INCLUDED_KEYEVENTPIPELINE_H

#include "keyeventbuffer.h"
#include "keyeventstage.h"
#include "keyeventsource.h"
#include "keyevent.h"

#include <cstdint>

class KeyEventPipeline
{
public:
    KeyEventPipeline(KeyEventSource& source,
                     KeyEventBuffer& buffer,
                     KeyEventStage&  next);

public:
    template <typename EventFunc>
    void poll(const EventFunc& eventFunc);

private:
    uint32_t nowMs() const;
    
private:
    KeyEventSource& mSource;
    KeyEventBuffer& mBuffer;
    KeyEventStage&  mNext;
};


inline
KeyEventPipeline::KeyEventPipeline(KeyEventSource& source,
                                   KeyEventBuffer& buffer,
                                   KeyEventStage&  next)
    : mSource(source)
    , mBuffer(buffer)
    , mNext(next)
{ }


template <typename EventFunc>
void KeyEventPipeline::poll(const EventFunc& eventFunc)
{
    mSource.pollKeyEvent(nowMs());

    if (!mBuffer.empty())
    {
        eventFunc(mBuffer.pop(), mNext);
    }
}

#endif /* INCLUDED_KEYEVENTPIPELINE_H */
