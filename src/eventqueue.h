#ifndef INCLUDED_EVENTQUEUE_H
#define INCLUDED_EVENTQUEUE_H

#include "types/circularbuffer.h"
#include "keyevent.h"

class EventQueue : public Types::CircularBuffer<KeyEvent, 240>
{
public:
    EventQueue();
};


inline
EventQueue::EventQueue()
    : CircularBuffer<KeyEvent, 240>()
{ }


#endif
