#ifndef INCLUDED_ACTIONEVENT_H
#define INCLUDED_ACTIONEVENT_H

#include "event/event.h"

class ActionEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kAction;

public:
    enum class Type : uint8_t
    {
        kBootloader       = 0,
        kDumpEntropyPool  = 1,
        kLockSecureMacros = 2
    };
    
public:
    static constexpr Event create(Type actionId);
    
private:
    explicit constexpr ActionEvent(const Event& event);
    
public:
    Type type;

private:
    friend class Event;
};


inline
constexpr Event ActionEvent::create(Type actionId)
{
    return Event(kType, static_cast<uint8_t>(actionId));
}

inline
constexpr ActionEvent::ActionEvent(const Event& event)
    : type(static_cast<Type>(event.value()))
{ }

#endif
