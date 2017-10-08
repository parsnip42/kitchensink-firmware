#ifndef INCLUDED_ACTIONPROCESSOR_H
#define INCLUDED_ACTIONPROCESSOR_H

#include "event/eventstage.h"

class EntropyPool;
class KeyboardState;

class ActionProcessor : public EventStage
{    
public:
    ActionProcessor(KeyboardState& keyboardState,
                    EntropyPool&   entropyPool,
                    EventStage&    next);

public:
    virtual bool processEvent(const Event& event) override;
    
private:
    KeyboardState& mKeyboardState;
    EntropyPool&   mEntropyPool;
    EventStage&    mNext;
    
private:
    ActionProcessor(const ActionProcessor&) = delete;
    ActionProcessor& operator=(const ActionProcessor&) = delete;
};

#endif
