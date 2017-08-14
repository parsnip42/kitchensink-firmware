#ifndef INCLUDED_SCREENEVENT_H
#define INCLUDED_SCREENEVENT_H

#include "event/event.h"
#include "screenid.h"

class ScreenEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kScreen;

public:
    static constexpr Event create(ScreenId::Type type,
                                  uint8_t        index);
    
private:
    explicit constexpr ScreenEvent(const Event& event);
    
public:
    ScreenId::Type type;
    uint8_t        index;

private:
    friend class Event;
};


inline
constexpr Event ScreenEvent::create(ScreenId::Type type,
                                    uint8_t        index)
{
    return Event(kType,
                 static_cast<uint8_t>(type),
                 index);
}

inline
constexpr ScreenEvent::ScreenEvent(const Event& event)
    : type(static_cast<ScreenId::Type>(event.subType()))
    , index(event.value())
{ }

#endif
