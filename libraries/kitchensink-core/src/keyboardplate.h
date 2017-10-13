#ifndef INCLUDED_KEYBOARDPLATE_H
#define INCLUDED_KEYBOARDPLATE_H

#include "hardware/keymask.h"

// FIXME: Eventually refactor this thing elsewhere.
#include "i2ckeymatrix.h"

#include "hardware/debounce.h"
#include "hardware/keyhardware.h"
#include "hardware/keyhardwareeventdispatcher.h"

#include <cstdint>

class EntropyPool;
class KeyHardwareEventHandler;

class KeyboardPlate : public KeyHardware
{
public:
    KeyboardPlate(uint8_t                                       matrixAddr,
                  uint16_t                                      matrixRowMask,
                  uint16_t                                      matrixColMask,
                  const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                  const std::array<uint8_t, KeyMask::kColumns>& columnMapping,
                  EntropyPool&                                  entropyPool);

public:
    virtual void poll(uint32_t                       timeMs,
                      const KeyHardwareEventHandler& eventHandler) override;

    virtual void pressed(const KeyHardwareEventHandler& eventHandler) override;
    
    virtual bool any() const override;

private:
    KeyMask                    mState;
    I2CKeyMatrix               mMatrix;
    Debounce                   mDebounce;
    KeyHardwareEventDispatcher mDispatcher;

private:
    KeyboardPlate(const KeyboardPlate&) = delete;
    KeyboardPlate& operator=(const KeyboardPlate&) = delete;
};

#endif
