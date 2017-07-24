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
    explicit KeyEventBuffer(KeyEventSource& prev);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void nextKeyEvent(KeyEventStage& next) override;

public:
    bool empty() const;
    KeyEvent pop();

private:
    KeyEventSource&              mPrev;
    CircularBuffer<KeyEvent, 40> mBuffer;

};


inline
KeyEventBuffer::KeyEventBuffer(KeyEventSource& prev)
    : mPrev(prev)
{ }

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
