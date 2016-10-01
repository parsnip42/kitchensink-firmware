#include "usbkeyboard.h"

#include <usb_keyboard.h>
#include <cstring>

UsbKeyboard::UsbKeyboard()
{
    clear();
}

void UsbKeyboard::setKey(int keyId)
{
    if (!(mKeyMask[keyId >> 3] & (1 << (keyId & 0x7)))
         && (mKeyNum < 6))
    {
        keyboard_keys[mKeyNum++] = keyId;
        mKeyMask[keyId >> 3] |= (1 << (keyId & 0x7));
    }
}

void UsbKeyboard::setModifier(int modifierId)
{
    keyboard_modifier_keys |= modifierId;
}

void UsbKeyboard::markDirty()
{
    mDirty = true;
}

void UsbKeyboard::update()
{
    if (mDirty)
    {
        usb_keyboard_send();
    }
    
    clear();
}

void UsbKeyboard::clear()
{
    mDirty = false;
    mKeyNum = 0;
    
    keyboard_modifier_keys = 0;
    keyboard_keys[0] = 0;
    keyboard_keys[1] = 0;
    keyboard_keys[2] = 0;
    keyboard_keys[3] = 0;
    keyboard_keys[4] = 0;
    keyboard_keys[5] = 0;

    std::memset(mKeyMask, 0, sizeof(mKeyMask));
}
