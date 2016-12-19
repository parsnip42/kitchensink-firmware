#ifndef INCLUDED_LOCKPROCESSOR_H
#define INCLUDED_LOCKPROCESSOR_H

#include "lockset.h"
#include "tapping.h"

class EventQueue;
class KeyEvent;

class LockProcessor
{
public:
    constexpr LockProcessor();

public:
    bool processEvent(LockSet&        lockSet,
                      const KeyEvent& event,
                      EventQueue&     eventQueue);

private:
    Tapping mTapping;
};


inline
constexpr LockProcessor::LockProcessor()
    : mTapping(500)
{ }

#endif
