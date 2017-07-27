#ifndef INCLUDED_LOCKPROCESSOR_H
#define INCLUDED_LOCKPROCESSOR_H

#include "lockset.h"
#include "keyeventstage.h"

class KeyEvent;

class LockProcessor : public KeyEventStage
{
public:
    explicit LockProcessor(LockSet&       lockSet,
                           KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

private:
    LockSet&       mLockSet;
    KeyEventStage& mNext;
};


inline
LockProcessor::LockProcessor(LockSet&       lockSet,
                             KeyEventStage& next)
    : mLockSet(lockSet)
    , mNext(next)
{ }

#endif
