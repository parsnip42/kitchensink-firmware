#ifndef INCLUDED_MULTIKEYPROCESSOR_H
#define INCLUDED_MULTIKEYPROCESSOR_H

#include "multikeyset.h"
#include "keyeventstage.h"
#include "timer.h"

#include <cstdint>

class KeyEvent;

class MultiKeyProcessor : public KeyEventStage
{
public:
    MultiKeyProcessor(MultiKeySet&   multiSet,
                      Timer&         timer,
                      KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

private:
    MultiKeySet&      mMultiKeySet;
    Timer::Handle  mReleaseTimer;
    std::size_t    mLast;
    uint8_t        mTaps;
    KeyEventStage& mNext;
};

inline
MultiKeyProcessor::MultiKeyProcessor(MultiKeySet&   multiSet,
                                     Timer&         timer,
                                     KeyEventStage& next)
    : mMultiKeySet(multiSet)
    , mReleaseTimer(timer.createHandle())
    , mLast(0)
    , mTaps(0)
    , mNext(next)
{ }

#endif
