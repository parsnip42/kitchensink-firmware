#ifndef INCLUDED_EVENTSTAGE_H
#define INCLUDED_EVENTSTAGE_H

class Event;

class EventStage
{
public:
    EventStage() = default;
    virtual ~EventStage() = default;
    
public:
    virtual void processEvent(const Event& event) = 0;
};

#endif
