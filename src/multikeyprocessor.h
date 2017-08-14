#ifndef INCLUDED_MULTIKEYPROCESSOR_H
#define INCLUDED_MULTIKEYPROCESSOR_H

#include "multikeyset.h"
#include "eventstage.h"
#include "timer.h"

#include <cstdint>

class Event;

class MultiKeyProcessor : public EventStage
{
public:
    MultiKeyProcessor(MultiKeySet& multiSet,
                      Timer&       timer,
                      EventStage&  next);

public:
    virtual void processEvent(const Event& event) override;

private:
    MultiKeySet&  mMultiKeySet;
    Timer::Handle mReleaseTimer;
    std::size_t   mLast;
    uint8_t       mTaps;
    EventStage&   mNext;
};

inline
MultiKeyProcessor::MultiKeyProcessor(MultiKeySet& multiSet,
                                     Timer&       timer,
                                     EventStage&  next)
    : mMultiKeySet(multiSet)
    , mReleaseTimer(timer.createHandle())
    , mLast(0)
    , mTaps(0)
    , mNext(next)
{ }

#endif
