#ifndef INCLUDED_DEBOUNCE_H
#define INCLUDED_DEBOUNCE_H

#include "keymask.h"

class Debounce
{
private:
    static constexpr unsigned int kLatency = 3;
    
public:
    constexpr Debounce();

public:
    bool process(const KeyMask& next);
    
    const KeyMask& state() const;
    const KeyMask& delta() const;
    
private:
    unsigned int mCounter;
    KeyMask      mCurrent;
    KeyMask      mState;
    KeyMask      mDelta;
    
private:
    Debounce(const Debounce&) = delete;
    Debounce& operator=(const Debounce&) = delete;
};

inline
constexpr Debounce::Debounce()
    : mCounter(0)
{ }

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
