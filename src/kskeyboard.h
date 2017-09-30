#ifndef INCLUDED_KSKEYBOARD_H
#define INCLUDED_KSKEYBOARD_H

#include "keymatrixevent.h"
#include "keymatrixeventhandler.h"
#include "keyboardplate.h"
#include "layerstack.h"

#include <cstdint>

class EntropyPool;

class KsKeyboard
{
public:
    typedef KeyMatrixEvent        Event;
    typedef KeyMatrixEventHandler EventHandler;

public:
    explicit KsKeyboard(EntropyPool& entropyPool);

public:
    void poll(uint32_t            timeMs,
              const EventHandler& callback); 

    void pressed(const EventHandler& callback);
    
    bool any() const;
    
private:
    KeyboardPlate mLeft;
    KeyboardPlate mRight;
    
private:
    KsKeyboard(const KsKeyboard&) = delete;
    KsKeyboard& operator=(const KsKeyboard&) = delete;
};


inline
void KsKeyboard::poll(uint32_t            timeMs,
                      const EventHandler& eventHandler)
{
    mLeft.poll(timeMs, eventHandler);
    mRight.poll(timeMs, eventHandler);
}

inline
void KsKeyboard::pressed(const EventHandler& eventHandler)
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

