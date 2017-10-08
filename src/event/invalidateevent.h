#ifndef INCLUDED_INVALIDATEEVENT_H
#define INCLUDED_INVALIDATEEVENT_H

#include "event/event.h"

class InvalidateEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kInvalidate;

public:
    enum class Type : uint8_t
    {
        kSmartKey = 0,
    };

public:
    static constexpr Event create(Type    type,
                                  uint8_t index = 0);

public:
    constexpr InvalidateEvent();
    constexpr InvalidateEvent(Type    type,
                              uint8_t index = 0);

private:
    explicit constexpr InvalidateEvent(const Event& event);
    
public:
    Type    type;
    uint8_t index;

private:
    friend class Event;
};


inline
bool operator==(const InvalidateEvent& lhs, const InvalidateEvent& rhs)
{
    return (lhs.type == rhs.type) && (lhs.index == rhs.index);
}

inline
bool operator!=(const InvalidateEvent& lhs, const InvalidateEvent& rhs)
{
    return !(lhs == rhs);
}


inline
constexpr Event InvalidateEvent::create(Type    type,
                                        uint8_t index)
{
    return Event(kType,
                 static_cast<uint8_t>(type),
                 index);
}

inline
constexpr InvalidateEvent::InvalidateEvent(const Event& event)
    : type(static_cast<Type>(event.subType()))
    , index(event.value())
{ }



#endif
