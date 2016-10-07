#ifndef INCLUDED_USBKEYBOARD_H
#define INCLUDED_USBKEYBOARD_H

#include <cstdint>

class UsbKeyboard
{
public:
    UsbKeyboard();

public:
    void setKey(int keyId);
    void setModifiers(uint8_t modifierMask);
    void markDirty();
    void update();

private:
    void clear();
    
private:
    bool    mDirty;
    int     mKeyNum;
    uint8_t mKeyMask[256 >> 3];
    
private:
    UsbKeyboard(const UsbKeyboard&) = delete;
    UsbKeyboard& operator=(const UsbKeyboard&) = delete;
};

#endif
    
