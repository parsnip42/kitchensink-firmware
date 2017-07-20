#ifndef INCLUDED_MULTIPROCESSOR_H
#define INCLUDED_MULTIPROCESSOR_H

#include "multiset.h"
#include "keyeventstage.h"

#include <cstdint>

class EventQueue;
class KeyEvent;

class MultiProcessor : public KeyEventStage
{
public:
    MultiProcessor(MultiSet&      multiSet,
                   KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

public:
    void tick(uint32_t timeMs);
    
private:
    MultiSet&      mMultiSet;
    std::size_t    mLast;
    uint32_t       mTapTime;
    uint8_t        mTaps;
    KeyEventStage& mNext;
};

inline
MultiProcessor::MultiProcessor(MultiSet&      multiSet,
                               KeyEventStage& next)
    : mMultiSet(multiSet)
    , mLast(0)
    , mTapTime(0)
    , mTaps(0)
    , mNext(next)
{ }

#endif /* INCLUDED_MULTIPROCESSOR_H */
