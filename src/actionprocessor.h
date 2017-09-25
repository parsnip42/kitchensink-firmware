#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "event/eventstage.h"

#include <array>

class EntropyPool;
class Event;

class ActionProcessor : public EventStage
{    
public:
    ActionProcessor(EntropyPool& entropyPool,
                    EventStage&  next);

public:
    virtual bool processEvent(const Event& event) override;
    
private:
    EntropyPool& mEntropyPool;
    EventStage&  mNext;
    
private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
