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
    typedef std::array<EventSource*, Size> Entries;
    
public:
    explicit CompositeEventSource(const Entries& entries);

public:
    virtual void pollEvent(EventStage& next) override;
    virtual bool flushEvents(EventStage& next) override;
    
private:
    Entries mEntries;

private:
    CompositeEventSource(const CompositeEventSource&) = delete;
    CompositeEventSource& operator=(const CompositeEventSource&) = delete;
};


template <std::size_t Size>
inline
CompositeEventSource<Size>::CompositeEventSource(const Entries& entries)
    : mEntries(entries)
{ }

template <std::size_t Size>
inline
void CompositeEventSource<Size>::pollEvent(EventStage& next)
{
    for (auto entry : mEntries)
    {
        entry->pollEvent(next);
    }
}

template <std::size_t Size>
inline
bool CompositeEventSource<Size>::flushEvents(EventStage& next)
{
    bool more(false);
        
    for (auto entry : mEntries)
    {
        more |= entry->flushEvents(next);
    }

    return more;
}

#endif
