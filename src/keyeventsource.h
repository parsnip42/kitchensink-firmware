#ifndef INCLUDED_KEYEVENTSOURCE_H
#define INCLUDED_KEYEVENTSOURCE_H

#include <cstdint>

class KeyEventStage;

class KeyEventSource
{
public:
    KeyEventSource() = default;
    virtual ~KeyEventSource() = default;

public:
    virtual void pollKeyEvent(uint32_t timeMs, KeyEventStage& next) = 0;
};

#endif /* INCLUDED_KEYEVENTSOURCE_H */
