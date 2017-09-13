#ifndef INCLUDED_MACROEVENT_H
#define INCLUDED_MACROEVENT_H

#include "event/event.h"

class MacroEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kMacro;

public:
    enum class Type : uint8_t
    {
        kDefault = 0,
        kSecure  = 1
    };
    
public:
    static constexpr Event create(Type type, uint8_t macroId);
    
private:
    explicit constexpr MacroEvent(const Event& event);
    
public:
    Type    type;
    uint8_t macroId;
    bool    pressed;

private:
    friend class Event;
};


inline
constexpr Event MacroEvent::create(Type type, uint8_t macroId)
{
    return Event(kType, 0, macroId);
}

inline
constexpr MacroEvent::MacroEvent(const Event& event)
    : type(Type::kDefault)
    , macroId(event.value())
    , pressed(!event.inverted())
{ }

#endif
