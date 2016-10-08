#ifndef INCLUDED_KEYBOARDPLATE_H
#define INCLUDED_KEYBOARDPLATE_H

#include "keymatrix.h"
#include "debounce.h"
#include "eventdispatcher.h"

class KeyboardPlate
{
public:
    KeyboardPlate(int                               matrixAddr,
                  uint16_t                          matrixRowMask,
                  uint16_t                          matrixColMask,
                  int                               debounceLatency,
                  const std::initializer_list<int>& rowMapping,
                  const std::initializer_list<int>& columnMapping);

public:
    bool scan();

    template <typename Callback>
    void dispatch(const Callback& callback);

private:
    KeyMatrix       mMatrix;
    Debounce        mDebounce;
    EventDispatcher mDispatcher;

private:
    KeyboardPlate(const KeyboardPlate&);
    KeyboardPlate& operator=(const KeyboardPlate&);
};

template <typename Callback>
inline
void KeyboardPlate::dispatch(const Callback& callback)
{
    mDispatcher.dispatch(mDebounce.state(),
                         mDebounce.delta(),
                         callback);
};

#endif