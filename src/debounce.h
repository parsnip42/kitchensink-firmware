#ifndef INCLUDED_DEBOUNCE_H
#define INCLUDED_DEBOUNCE_H

#include "keymatrix.h"

class Debounce
{
public:
    explicit Debounce(unsigned int latency);

public:
    bool process(const KeyMatrix::Mask& next);
    
    const KeyMatrix::Mask& state() const;
    const KeyMatrix::Mask& delta() const;
    
private:
    const unsigned int mLatency;
    unsigned int       mCounter;
    KeyMatrix::Mask    mCurrent;
    KeyMatrix::Mask    mState;
    KeyMatrix::Mask    mDelta;
    
private:
    Debounce(const Debounce&) = delete;
    Debounce& operator=(const Debounce&) = delete;
};

inline
const KeyMatrix::Mask& Debounce::state() const
{
    return mState;
}

inline
const KeyMatrix::Mask& Debounce::delta() const
{
    return mDelta;
}

#endif
