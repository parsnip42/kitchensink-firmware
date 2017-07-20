#ifndef INCLUDED_DELAYPROCESSOR_H
#define INCLUDED_DELAYPROCESSOR_H

#include "keyeventstage.h"

class KeyEvent;

class DelayProcessor : public KeyEventStage
{
public:
    explicit DelayProcessor(KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
private:
    KeyEventStage& mNext;
};

inline
DelayProcessor::DelayProcessor(KeyEventStage& next)
    : mNext(next)
{ }

#endif /* INCLUDED_DELAYPROCESSOR_H */
