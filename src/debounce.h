#ifndef INCLUDED_DEBOUNCE_H
#define INCLUDED_DEBOUNCE_H

#include "keymask.h"

class Debounce
{
private:
    static constexpr uint32_t kLatencyMs = 5;
    
public:
    constexpr Debounce();

public:
    bool process(uint32_t       timeMs,
                 const KeyMask& next);
    
    const KeyMask& state() const;
    const KeyMask& delta() const;
    
private:
    uint32_t mLastMs;
    KeyMask  mCurrent;
    KeyMask  mState;
    KeyMask  mDelta;
    
private:
    Debounce(const Debounce&) = delete;
    Debounce& operator=(const Debounce&) = delete;
};

inline
constexpr Debounce::Debounce()
    : mLastMs(0)
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
