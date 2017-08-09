#ifndef INCLUDED_KSKEYBOARD_H
#define INCLUDED_KSKEYBOARD_H

#include "keymatrixevent.h"
#include "keyboardplate.h"
#include "layerstack.h"
#include "hardware/entropypool.h"

#include <cstdint>

class KsKeyboard
{
public:
    typedef KeyMatrixEvent Event;
    
public:
    KsKeyboard();

public:
    template <typename Callback>
    void poll(uint32_t        timeMs,
              const Callback& callback); 

    template <typename Callback>
    void pressed(const Callback& callback);
    
    bool any() const;

private:
    KeyboardPlate mLeft;
    KeyboardPlate mRight;
    EntropyPool   mEntropyPool;
    
private:
    KsKeyboard(const KsKeyboard&) = delete;
    KsKeyboard& operator=(const KsKeyboard&) = delete;
};


template <typename Callback>
inline
void KsKeyboard::poll(uint32_t        timeMs,
                      const Callback& callback)
{
    mLeft.poll(timeMs, callback);
    mRight.poll(timeMs, callback);
}

template <typename Callback>
inline
void KsKeyboard::pressed(const Callback& callback)
{
    mLeft.pressed(callback);
    mRight.pressed(callback);
}

inline
bool KsKeyboard::any() const
{
    return mLeft.any() || mRight.any();
}

#endif
