#ifndef INCLUDED_EVENTLOGGER_H
#define INCLUDED_EVENTLOGGER_H

#include "event/eventstage.h"

class EventLogger : public EventStage
{
public:
    static void logEvent(const Event& event);
    
public:
    explicit EventLogger(EventStage& next);

public:
    virtual bool processEvent(const Event& event) override;

private:
    EventStage& mNext;
};


inline
EventLogger::EventLogger(EventStage& next)
    : mNext(next)
{ }

#endif
