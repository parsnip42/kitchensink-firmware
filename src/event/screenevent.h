#ifndef INCLUDED_SCREENEVENT_H
#define INCLUDED_SCREENEVENT_H

#include "event/event.h"

class ScreenEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kScreen;

public:
    enum class Type : uint8_t
    {
        kHome           = 0,
        kMenu           = 1,
        kScreen         = 2,
        kEditMacro      = 3,
        kEditSMacro     = 4,
        kRecordMacro    = 5,
        kRecordMacroRT  = 6,
        kRecordSMacro   = 7,
        kRecordSMacroRT = 8,
        kEditLayer      = 9,
        kEditMulti      = 10,
        kEditSmart      = 11,
    };

public:
    static constexpr Event create(Type    type,
                                  uint8_t index = 0);

public:
    constexpr ScreenEvent();
    constexpr ScreenEvent(Type    type,
                          uint8_t index);

private:
    explicit constexpr ScreenEvent(const Event& event);
    
public:
    Type    type;
    uint8_t index;

private:
    friend class Event;
};


inline
bool operator==(const ScreenEvent& lhs, const ScreenEvent& rhs)
{
    return (lhs.type == rhs.type) && (lhs.index == rhs.index);
}

inline
bool operator!=(const ScreenEvent& lhs, const ScreenEvent& rhs)
{
    return !(lhs == rhs);
}


inline
constexpr Event ScreenEvent::create(Type    type,
                                    uint8_t index)
{
    return Event(kType,
                 static_cast<uint8_t>(type),
                 index);
}

inline
constexpr ScreenEvent::ScreenEvent()
    : type(Type::kHome)
    , index(0)
{ }

inline
constexpr ScreenEvent::ScreenEvent(Type    nType,
                                   uint8_t nIndex)
    : type(nType)
    , index(nIndex)
{ }

inline
constexpr ScreenEvent::ScreenEvent(const Event& event)
    : type(static_cast<Type>(event.subType()))
    , index(event.value())
{ }

#endif


