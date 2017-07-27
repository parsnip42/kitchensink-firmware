#ifndef INCLUDED_KEYEVENTBUFFER_H
#define INCLUDED_KEYEVENTBUFFER_H

#include "keyeventstage.h"
#include "keyeventsource.h"
#include "keyevent.h"
#include "types/circularbuffer.h"

class KeyEventBuffer : public KeyEventStage
                     , public KeyEventSource
{
public:
    KeyEventBuffer() = default;

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void pollKeyEvent(uint32_t timeMs, KeyEventStage& next) override;

public:
    bool empty() const;
    KeyEvent pop();

private:
    CircularBuffer<KeyEvent, 200> mBuffer;
};


inline
bool KeyEventBuffer::empty() const
{
    return mBuffer.empty();
}

inline
KeyEvent KeyEventBuffer::pop()
{
    return mBuffer.pop();
}


#endif /* INCLUDED_KEYEVENTBUFFER_H */
