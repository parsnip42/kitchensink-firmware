#ifndef INCLUDED_SMARTKEYPROCESSOR_H
#define INCLUDED_SMARTKEYPROCESSOR_H

#include "event/eventstage.h"
#include "smartkeyset.h"

class SmartKeyProcessor : public EventStage
{
public:
    SmartKeyProcessor(SmartKeySet& smartKeys,
                      EventStage&  next);

public:
    virtual bool processEvent(const Event& event) override;
    
private:
    SmartKeySet& mSmartKeys;
    EventStage&  mNext;
};

#endif
