#ifndef INCLUDED_DEBOUNCE_H
#define INCLUDED_DEBOUNCE_H

#include <cstdint>

template <typename KeyMask>
class Debounce
{
private:
    static constexpr uint32_t kLatencyMs = 7;
    
public:
    constexpr Debounce();

public:
    bool process(uint32_t       timeMs,
                 const KeyMask& next);
    
public:
    KeyMask state;
    KeyMask delta;

private:
    uint32_t mLastMs;
    KeyMask mCurrent;
    
private:
    Debounce(const Debounce&) = delete;
    Debounce& operator=(const Debounce&) = delete;
};


template <typename KeyMask>
inline
constexpr Debounce<KeyMask>::Debounce()
    : mLastMs(0)
{ }

template <typename KeyMask>
inline
bool Debounce<KeyMask>::process(uint32_t        timeMs,
                                 const KeyMask& next)
{
    mCurrent &= next;
    
    if (timeMs >= (mLastMs + kLatencyMs))
    {
        delta = state;
        delta ^= mCurrent;
        state = mCurrent;
        
        mCurrent = next;
        mLastMs = timeMs;
        
        return !delta.empty();
    }
    
    return false;
}

#endif
