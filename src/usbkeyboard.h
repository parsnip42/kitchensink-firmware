#ifndef INCLUDED_USBKEYBOARD_H
#define INCLUDED_USBKEYBOARD_H

#include "keyeventstage.h"

#include <cstdint>

class KeyEvent;

class UsbKeyboard : public KeyEventStage
{
public:
    UsbKeyboard();

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

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
    
