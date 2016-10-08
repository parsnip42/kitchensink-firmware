#include "usbkeyboard.h"

#include <usb_keyboard.h>
#include <cstring>

UsbKeyboard::UsbKeyboard()
    : mKeyNum(0)
{
    keyboard_keys[0] = 0;
    keyboard_keys[1] = 0;
    keyboard_keys[2] = 0;
    keyboard_keys[3] = 0;
    keyboard_keys[4] = 0;
    keyboard_keys[5] = 0;
    keyboard_modifier_keys = 0;

    std::memset(mKeyMask, 0, sizeof(mKeyMask));
}


void UsbKeyboard::pressKey(int keyId)
{
    if (!(mKeyMask[keyId >> 3] & (1 << (keyId & 0x7)))
         && (mKeyNum < 6))
    {
        keyboard_keys[mKeyNum++] = keyId;
        mKeyMask[keyId >> 3] |= (1 << (keyId & 0x7));
    }

    usb_keyboard_send();
}

void UsbKeyboard::releaseKey(int keyId)
{
    for (int i = 0; i < mKeyNum; ++i)
    {
        if (keyboard_keys[i] == keyId)
        {
            keyboard_keys[i] = keyboard_keys[--mKeyNum];
            keyboard_keys[mKeyNum] = 0;
            mKeyMask[keyId >> 3] &= ~(1 << (keyId & 0x7));
            break;
        }
    }
    
    usb_keyboard_send();
}


void UsbKeyboard::setModifiers(uint8_t modifierMask)
{
    keyboard_modifier_keys = modifierMask;
    usb_keyboard_send();
}
