#ifndef INCLUDED_USBKEYBOARD_H
#define INCLUDED_USBKEYBOARD_H

#include "keystate.h"

#include <cstdint>

class UsbKeyboard
{
public:
    UsbKeyboard();

public:
    void processKey(int keyCode, KeyState state);
    void processModifier(int modifier, KeyState state);

private:
    void pressKey(int keyCode);
    void releaseKey(int keyCode);

private:
    int     mKeyNum;
    uint8_t mKeyMask[256 >> 3];
    
private:
    UsbKeyboard(const UsbKeyboard&) = delete;
    UsbKeyboard& operator=(const UsbKeyboard&) = delete;
};

#endif
    
