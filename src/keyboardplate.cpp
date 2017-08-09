#include "keyboardplate.h"

KeyboardPlate::KeyboardPlate(const int                                     matrixAddr,
                             const uint16_t                                matrixRowMask,
                             const uint16_t                                matrixColMask,
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
