#ifndef INCLUDED_KSKEYBOARD_H
#define INCLUDED_KSKEYBOARD_H

#include "keymatrixevent.h"
#include "keymatrixeventhandler.h"
#include "keyboardplate.h"
#include "layerstack.h"
#include "hardware/keyhardware.h"

#include <cstdint>

class EntropyPool;

class KsKeyboard : public KeyHardware
{
public:
    explicit KsKeyboard(EntropyPool& entropyPool);

public:
    virtual void poll(uint32_t                     timeMs,
                      const KeyMatrixEventHandler& callback) override;

    virtual void pressed(const KeyMatrixEventHandler& callback) override;
    
    virtual bool any() const override;
    
private:
    KeyboardPlate mLeft;
    KeyboardPlate mRight;
    
private:
    KsKeyboard(const KsKeyboard&) = delete;
    KsKeyboard& operator=(const KsKeyboard&) = delete;
};


inline
void KsKeyboard::poll(uint32_t                     timeMs,
                      const KeyMatrixEventHandler& eventHandler)
{
    mLeft.poll(timeMs, eventHandler);
    mRight.poll(timeMs, eventHandler);
}

inline
void KsKeyboard::pressed(const KeyMatrixEventHandler& eventHandler)
{
    mLeft.pressed(eventHandler);
    mRight.pressed(eventHandler);
}

inline
bool KsKeyboard::any() const
{
    return mLeft.any() || mRight.any();
}

#endif

