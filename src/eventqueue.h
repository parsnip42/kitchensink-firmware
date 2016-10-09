#ifndef INCLUDED_EVENTQUEUE_H
#define INCLUDED_EVENTQUEUE_H

#include "circularbuffer.h"
#include "keyevent.h"

class EventQueue : public CircularBuffer<KeyEvent, 100>
{
public:
    EventQueue();
};


inline
EventQueue::EventQueue()
    : CircularBuffer<KeyEvent, 100>()
{ }


#endif
