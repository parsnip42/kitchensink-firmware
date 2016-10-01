#ifndef INCLUDED_USBKEYBOARD_H
#define INCLUDED_USBKEYBOARD_H

class UsbKeyboard
{
public:
    UsbKeyboard();

public:
    void setKey(int keyId);
    void setModifier(int modifierId);
    void send();
    void clear();
    
private:
    int mKeyNum;

private:
    UsbKeyboard(const UsbKeyboard&) = delete;
    UsbKeyboard& operator=(const UsbKeyboard&) = delete;
};

#endif
    
