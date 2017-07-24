#ifndef INCLUDED_KEYEVENTSOURCE_H
#define INCLUDED_KEYEVENTSOURCE_H

#include "keyevent.h"

class KeyEventStage;

class KeyEventSource
{
public:
    KeyEventSource() = default;
    virtual ~KeyEventSource() = default;

public:
    virtual void nextKeyEvent(KeyEventStage& next) = 0;
};

#endif /* INCLUDED_KEYEVENTSOURCE_H */
