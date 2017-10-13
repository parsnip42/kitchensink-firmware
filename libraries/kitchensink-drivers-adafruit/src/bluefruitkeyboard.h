#ifndef INCLUDED_BLUEFRUITKEYBOARD_H
#define INCLUDED_BLUEFRUITKEYBOARD_H

#include "event/eventstage.h"
#include "data/keycode.h"

#include <array>
#include <cstdint>

class BluefruitKeyboard : public EventStage
{
public:
    BluefruitKeyboard();
    
public:
    virtual bool processEvent(const Event& event) override;

private:
    void pressKey(KeyCode key);
    void releaseKey(KeyCode key);

private:
    void update();
    
private:
    uint8_t                mModifiers;
    std::array<uint8_t, 6> mKeys;
    int                    mKeyNum;
    uint8_t                mKeyMask[256 >> 3];
    bool                   mDirty;
    
private:
    BluefruitKeyboard(const BluefruitKeyboard&) = delete;
    BluefruitKeyboard& operator=(const BluefruitKeyboard&) = delete;
};

#endif
