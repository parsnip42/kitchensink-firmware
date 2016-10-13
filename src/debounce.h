#ifndef INCLUDED_DEBOUNCE_H
#define INCLUDED_DEBOUNCE_H

#include "keymask.h"

class Debounce
{
public:
    explicit Debounce(unsigned int latency);

public:
    bool process(const KeyMask& next);
    
    const KeyMask& state() const;
    const KeyMask& delta() const;
    
private:
    const unsigned int mLatency;
    unsigned int       mCounter;
    KeyMask            mCurrent;
    KeyMask            mState;
    KeyMask            mDelta;
    
private:
    Debounce(const Debounce&) = delete;
    Debounce& operator=(const Debounce&) = delete;
};

inline
const KeyMask& Debounce::state() const
{
    return mState;
}

inline
const KeyMask& Debounce::delta() const
{
    return mDelta;
}

#endif
