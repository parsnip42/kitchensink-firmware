#ifndef INCLUDED_LOCKPROCESSOR_H
#define INCLUDED_LOCKPROCESSOR_H

#include "lockset.h"
#include "keyeventstage.h"
#include "tapping.h"

class KeyEvent;

class LockProcessor : public KeyEventStage
{
public:
    explicit LockProcessor(LockSet&       lockSet,
                           KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

private:
    Tapping        mTapping;
    LockSet&       mLockSet;
    KeyEventStage& mNext;
};


inline
LockProcessor::LockProcessor(LockSet&       lockSet,
                             KeyEventStage& next)
    : mTapping(500)
    , mLockSet(lockSet)
    , mNext(next)
{ }

#endif
