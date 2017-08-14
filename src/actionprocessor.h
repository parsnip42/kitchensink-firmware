#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "event/eventstage.h"

#include <array>

class Event;

class ActionProcessor : public EventStage
{    
public:
    explicit ActionProcessor(EventStage& next);

public:
    virtual void processEvent(const Event& event) override;
    
private:
    EventStage& mNext;
    
private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
