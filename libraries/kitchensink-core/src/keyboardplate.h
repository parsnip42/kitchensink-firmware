#ifndef INCLUDED_KEYBOARDPLATE_H
#define INCLUDED_KEYBOARDPLATE_H

#include "hardware/keymask.h"
#include "hardware/i2ckeymatrix.h"
#include "hardware/debounce.h"
#include "keymatrixdispatcher.h"

#include <cstdint>

class EntropyPool;
class KeyHardwareEventHandler;

class KeyboardPlate
{
public:
    KeyboardPlate(const int                                     matrixAddr,
                  const uint16_t                                matrixRowMask,
                  const uint16_t                                matrixColMask,
                  const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                  const std::array<uint8_t, KeyMask::kColumns>& columnMapping,
                  EntropyPool&                                  entropyPool);

public:
    void poll(uint32_t                     timeMs,
              const KeyHardwareEventHandler& eventHandler);

    void pressed(const KeyHardwareEventHandler& eventHandler);
    
    bool any() const;

private:
    KeyMask             mState;
    I2CKeyMatrix        mMatrix;
    Debounce            mDebounce;
    KeyMatrixDispatcher mDispatcher;

private:
    KeyboardPlate(const KeyboardPlate&) = delete;
    KeyboardPlate& operator=(const KeyboardPlate&) = delete;
};


inline
void KeyboardPlate::poll(uint32_t                       timeMs,
                         const KeyHardwareEventHandler& eventHandler)
{
    mMatrix.scan(mState);
    
    if (mDebounce.process(timeMs, mState))
    {
        mDispatcher.dispatch(mDebounce.state(),
                             mDebounce.delta(),
                             eventHandler);
    }
}

inline
void KeyboardPlate::pressed(const KeyHardwareEventHandler& eventHandler)
{
    mDispatcher.dispatch(KeyMask(),
                         mDebounce.state(),
                         eventHandler);
}

inline
bool KeyboardPlate::any() const
{
    return !mDebounce.state().empty() || !mDebounce.delta().empty();
}

#endif
