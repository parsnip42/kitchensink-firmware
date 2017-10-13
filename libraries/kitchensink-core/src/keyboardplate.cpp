#include "keyboardplate.h"

KeyboardPlate::KeyboardPlate(uint8_t                                       matrixAddr,
                             uint16_t                                      matrixRowMask,
                             uint16_t                                      matrixColMask,
                             const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                             const std::array<uint8_t, KeyMask::kColumns>& columnMapping,
                             EntropyPool&                                  entropyPool)
    : mMatrix(matrixAddr,
              matrixRowMask,
              matrixColMask,
              entropyPool)
    , mDebounce()
    , mDispatcher(rowMapping,
                  columnMapping)
{ }

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

void KeyboardPlate::pressed(const KeyHardwareEventHandler& eventHandler)
{
    mDispatcher.dispatch(KeyMask(),
                         mDebounce.state(),
                         eventHandler);
}

bool KeyboardPlate::any() const
{
    return !mDebounce.state().empty() || !mDebounce.delta().empty();
}
