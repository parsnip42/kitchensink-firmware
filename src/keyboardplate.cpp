#include "keyboardplate.h"

KeyboardPlate::KeyboardPlate(int      matrixAddr,
                             uint16_t matrixRowMask,
                             uint16_t matrixColMask,
                             int      debounceLatency,
                             const std::initializer_list<int>& rowMapping,
                             const std::initializer_list<int>& columnMapping)
    : mMatrix(matrixAddr,
              matrixRowMask,
              matrixColMask)
    , mDebounce(debounceLatency)
    , mDispatcher(rowMapping,
                  columnMapping)
{ }

bool KeyboardPlate::scan()
{
    mMatrix.scan();
    
    return mDebounce.process(mMatrix.state());
}

void KeyboardPlate::dispatch(const EventDispatcher::Callback& callback)
{
    mDispatcher.dispatch(mDebounce.state(),
                         mDebounce.delta(),
                         callback);
}
