#ifndef INCLUDED_MULTIPROCESSOR_H
#define INCLUDED_MULTIPROCESSOR_H

#include "multiset.h"

#include <cstdint>

class EventQueue;
class KeyEvent;

class MultiProcessor
{
public:
    MultiProcessor()
        : mLast(0)
        , mTapTime(0)
        , mTaps(0)
    {
    }
    
public:
    void tick(MultiSet&   multiSet,
              uint32_t    timeMs,
              EventQueue& eventQueue);
    
    bool processEvent(MultiSet&       multiSet,
                      const KeyEvent& event,
                      uint32_t        timeMs,
                      EventQueue&     eventQueue);
    
private:
    std::size_t mLast;
    uint32_t    mTapTime;
    uint8_t     mTaps;
};

#endif /* INCLUDED_MULTIPROCESSOR_H */
