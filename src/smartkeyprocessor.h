#ifndef INCLUDED_SMARTKEYPROCESSOR_H
#define INCLUDED_SMARTKEYPROCESSOR_H

#include "eventstage.h"
#include "smartkeyset.h"

class SmartKeyProcessor : public EventStage
{
public:
    SmartKeyProcessor(SmartKeySet& smartKeys,
                      EventStage&  next);

public:
    virtual void processEvent(const Event& event) override;
    
private:
    SmartKeySet&   mSmartKeys;
    EventStage& mNext;
};

#endif
