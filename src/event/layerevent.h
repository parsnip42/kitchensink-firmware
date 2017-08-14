#ifndef INCLUDED_LAYEREVENT_H
#define INCLUDED_LAYEREVENT_H

#include "event/event.h"

class LayerEvent
{
public:
    static constexpr Event::Type kType = Event::Type::kLayer;

public:
    static constexpr Event create(int layerId);
    
private:
    explicit constexpr LayerEvent(const Event& event);
    
public:
    uint8_t layer;
    bool    enable;

private:
    friend class Event;
};


inline
constexpr Event LayerEvent::create(int layerId)
{
    return Event(kType, layerId);
}

inline
constexpr LayerEvent::LayerEvent(const Event& event)
    : layer(event.value())
    , enable(event.subType() == 0)
{ }

#endif
