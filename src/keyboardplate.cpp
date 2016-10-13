#include "keyboardplate.h"

KeyboardPlate::KeyboardPlate(const int                                       matrixAddr,
                             const uint16_t                                  matrixRowMask,
                             const uint16_t                                  matrixColMask,
                             const int                                       debounceLatency,
                             const std::array<uint8_t, KeyMatrix::kRows>&    rowMapping,
                             const std::array<uint8_t, KeyMatrix::kColumns>& columnMapping)
    : mMatrix(matrixAddr,
              matrixRowMask,
              matrixColMask)
    , mDebounce(debounceLatency)
    , mDispatcher(rowMapping,
                  columnMapping)
{ }
