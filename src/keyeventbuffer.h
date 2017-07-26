#ifndef INCLUDED_KEYEVENTBUFFER_H
#define INCLUDED_KEYEVENTBUFFER_H

#include "keyeventstage.h"
#include "keyevent.h"
#include "types/circularbuffer.h"

class KeyEventBuffer : public KeyEventStage
{
public:
    KeyEventBuffer() = default;

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

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
