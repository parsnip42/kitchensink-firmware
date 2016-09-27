#ifndef INCLUDED_USBKEYBOARD_H
#define INCLUDED_USBKEYBOARD_H

#include <cstdint>

class UsbKeyboard
{
public:
    UsbKeyboard();

public:
    void setKey(uint8_t keyId);
    void setModifier(uint8_t modifierId);
    void send();

private:
    void clear();
    
private:
    int mKeyNum;

private:
    UsbKeyboard(const UsbKeyboard&) = delete;
    UsbKeyboard& operator=(const UsbKeyboard&) = delete;
};

#endif
    
