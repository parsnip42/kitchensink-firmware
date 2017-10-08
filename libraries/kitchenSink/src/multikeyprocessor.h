#ifndef INCLUDED_MULTIKEYPROCESSOR_H
#define INCLUDED_MULTIKEYPROCESSOR_H

#include "multikeyset.h"
#include "event/eventstage.h"
#include "timer.h"

#include <cstdint>

class Event;
class GlobalConfig;

class MultiKeyProcessor : public EventStage
{
public:
    MultiKeyProcessor(MultiKeySet&  multiSet,
                      GlobalConfig& globalConfig,
                      Timer&        timer,
                      EventStage&   next);

public:
    virtual bool processEvent(const Event& event) override;

private:
    MultiKeySet&  mMultiKeySet;
    GlobalConfig& mGlobalConfig;
    Timer::Handle mReleaseTimer;
    std::size_t   mLast;
    uint8_t       mTaps;
    EventStage&   mNext;
};

inline
MultiKeyProcessor::MultiKeyProcessor(MultiKeySet&  multiSet,
                                     GlobalConfig& globalConfig,
                                     Timer&        timer,
                                     EventStage&   next)
    : mMultiKeySet(multiSet)
    , mGlobalConfig(globalConfig)
    , mReleaseTimer(timer.createHandle())
    , mLast(0)
    , mTaps(0)
    , mNext(next)
{ }

#endif
