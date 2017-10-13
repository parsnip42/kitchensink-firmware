#ifndef INCLUDED_KSKEYBOARD_H
#define INCLUDED_KSKEYBOARD_H

#include "keyboardplate.h"
#include "hardware/keyhardware.h"

#include <cstdint>

class EntropyPool;

class KsKeyboard : public KeyHardware
{
public:
    explicit KsKeyboard(EntropyPool& entropyPool);

public:
    virtual void poll(uint32_t                       timeMs,
                      const KeyHardwareEventHandler& handler) override;

    virtual void pressed(const KeyHardwareEventHandler& callback) override;
    
    virtual bool any() const override;
    
private:
    KeyboardPlate mLeft;
    KeyboardPlate mRight;
    
private:
    KsKeyboard(const KsKeyboard&) = delete;
    KsKeyboard& operator=(const KsKeyboard&) = delete;
};


inline
void KsKeyboard::poll(uint32_t                       timeMs,
                      const KeyHardwareEventHandler& handler)
{
    mLeft.poll(timeMs, handler);
    mRight.poll(timeMs, handler);
}

inline
void KsKeyboard::pressed(const KeyHardwareEventHandler& handler)
{
    mLeft.pressed(handler);
    mRight.pressed(handler);
}

inline
bool KsKeyboard::any() const
{
    return mLeft.any() || mRight.any();
}

#endif

