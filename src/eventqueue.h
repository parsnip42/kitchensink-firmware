#ifndef INCLUDED_EVENTQUEUE_H
#define INCLUDED_EVENTQUEUE_H

#include "circularbuffer.h"
#include "keyevent.h"

typedef CircularBuffer<KeyEvent, 100> EventQueue;

#endif
