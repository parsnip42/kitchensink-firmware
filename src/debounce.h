#ifndef INCLUDED_DEBOUNCE_H
#define INCLUDED_DEBOUNCE_H

#include <keymatrix.h>

class Debounce
{
public:
    explicit Debounce(int latency);

public:
    bool process(const KeyMatrix::Mask& next);
    
    const KeyMatrix::Mask& state() const;
    const KeyMatrix::Mask& delta() const;
    uint32_t filtered() const;
    
private:
    const int                         mLatency;
    std::array<int, KeyMatrix::kRows> mStableCount;
    KeyMatrix::Mask                   mState;
    KeyMatrix::Mask                   mLast;
    KeyMatrix::Mask                   mDelta;
    uint32_t                          mFiltered;
    
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

inline
uint32_t Debounce::filtered() const
{
    return mFiltered;
}

#endif
