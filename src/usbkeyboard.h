#ifndef INCLUDED_USBKEYBOARD_H
#define INCLUDED_USBKEYBOARD_H

#include <cstdint>

class UsbKeyboard
{
public:
    UsbKeyboard();

public:
    void processKey(uint8_t keyCode, bool pressed);
    
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
    
