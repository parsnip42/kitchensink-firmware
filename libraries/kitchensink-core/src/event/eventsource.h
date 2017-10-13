#ifndef INCLUDED_EVENTSOURCE_H
#define INCLUDED_EVENTSOURCE_H

class EventStage;

class EventSource
{
public:
    virtual void pollEvent(EventStage& next) = 0;
    virtual bool flushEvents(EventStage&);
};


inline
bool EventSource::flushEvents(EventStage&)
{
    return false;
}

#endif
