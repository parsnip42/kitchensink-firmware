#ifndef INCLUDED_COMPOSITEEVENTSOURCE_H
#define INCLUDED_COMPOSITEEVENTSOURCE_H

#include "event/eventsource.h"
#include "event/eventstage.h"

#include <array>
#include <cstdint>

template <std::size_t Size>
class CompositeEventSource : public EventSource
{
public:
    typedef std::array<EventSource*, Size> EventSources;
    
public:
    explicit CompositeEventSource(const EventSources& sources);

public:
    virtual void pollEvent(EventStage& next) override;
    virtual bool flushEvents(EventStage& next) override;
    
private:
    EventSources mSources;

private:
    CompositeEventSource(const CompositeEventSource&) = delete;
    CompositeEventSource& operator=(const CompositeEventSource&) = delete;
};


template <std::size_t Size>
inline
CompositeEventSource<Size>::CompositeEventSource(const EventSources& sources)
    : mSources(sources)
{ }

template <std::size_t Size>
inline
void CompositeEventSource<Size>::pollEvent(EventStage& next)
{
    for (auto source : mSources)
    {
        source->pollEvent(next);
    }
}

template <std::size_t Size>
inline
bool CompositeEventSource<Size>::flushEvents(EventStage& next)
{
    bool more(false);
        
    for (auto source : mSources)
    {
        more |= source->flushEvents(next);
    }

    return more;
}

#endif
