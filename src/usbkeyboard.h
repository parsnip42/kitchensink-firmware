#ifndef INCLUDED_USBKEYBOARD_H
#define INCLUDED_USBKEYBOARD_H

#include "keystate.h"

#include <cstdint>

class UsbKeyboard
{
public:
    UsbKeyboard();

public:
    void processKey(uint8_t keyCode, KeyState state);
    void processModifier(uint8_t modifier, KeyState state);
    void update();
    
private:
    void pressKey(uint8_t keyCode);
    void releaseKey(uint8_t keyCode);

private:
    int     mKeyNum;
    uint8_t mKeyMask[256 >> 3];
    bool    mDirty;
    
private:
    UsbKeyboard(const UsbKeyboard&) = delete;
    UsbKeyboard& operator=(const UsbKeyboard&) = delete;
};

#endif
    
