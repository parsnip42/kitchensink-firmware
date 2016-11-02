#ifndef INCLUDED_KEYBOARDPLATE_H
#define INCLUDED_KEYBOARDPLATE_H

#include "keymask.h"
#include "keymatrix.h"
#include "debounce.h"
#include "eventdispatcher.h"

class KeyboardPlate
{
public:
    KeyboardPlate(const int                                     matrixAddr,
                  const uint16_t                                matrixRowMask,
                  const uint16_t                                matrixColMask,
                  const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                  const std::array<uint8_t, KeyMask::kColumns>& columnMapping);

public:
    void init();

public:
    template <typename Callback>
    void poll(const Callback& callback);

    template <typename Callback>
    void pressed(const Callback& callback);
    
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
void KeyboardPlate::poll(const Callback& callback)
{
    mMatrix.scan();

    if (mDebounce.process(mMatrix.state()))
    {
        mDispatcher.dispatch(mDebounce.state(),
                             mDebounce.delta(),
                             callback);
    }
}

template <typename Callback>
void KeyboardPlate::pressed(const Callback& callback)
{
    mDispatcher.pressed(mDebounce.state(),
                        callback);
}


#endif
