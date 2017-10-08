#ifndef INCLUDED_EVENTSTAGE_H
#define INCLUDED_EVENTSTAGE_H

class Event;

/// Interface for event consumption.
class EventStage
{
public:
    EventStage() = default;
    virtual ~EventStage() = default;
    
public:
    /// Process an incoming event. Returns false if the event is explicitly
    /// ignored (usually widgets etc). Should return true in most cases.
    virtual bool processEvent(const Event& event) = 0;
};

#endif
