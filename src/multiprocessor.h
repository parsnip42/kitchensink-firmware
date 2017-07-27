#ifndef INCLUDED_MULTIPROCESSOR_H
#define INCLUDED_MULTIPROCESSOR_H

#include "multiset.h"
#include "keyeventstage.h"
#include "timer.h"

#include <cstdint>

class KeyEvent;

class MultiProcessor : public KeyEventStage
{
public:
    MultiProcessor(MultiSet&      multiSet,
                   Timer&         timer,
                   KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

private:
    MultiSet&      mMultiSet;
    Timer&         mTimer;
    Timer::Handle  mReleaseTimer;
    std::size_t    mLast;
    uint8_t        mTaps;
    KeyEventStage& mNext;
};

inline
MultiProcessor::MultiProcessor(MultiSet&      multiSet,
                               Timer&         timer,
                               KeyEventStage& next)
    : mMultiSet(multiSet)
    , mTimer(timer)
    , mLast(0)
    , mTaps(0)
    , mNext(next)
{ }

#endif /* INCLUDED_MULTIPROCESSOR_H */
