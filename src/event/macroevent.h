#ifndef INCLUDED_MACROEVENT_H
#define INCLUDED_MACROEVENT_H

#include "event/event.h"

class MacroEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kMacro;

public:
    static constexpr Event create(uint8_t macroId);
    
private:
    explicit constexpr MacroEvent(const Event& event);
    
public:
    uint8_t macroId;
    bool    pressed;

private:
    friend class Event;
};


inline
constexpr Event MacroEvent::create(uint8_t macroId)
{
    return Event(kType, macroId);
}

inline
constexpr MacroEvent::MacroEvent(const Event& event)
    : macroId(event.value())
    , pressed(!event.subType())
{ }

#endif
