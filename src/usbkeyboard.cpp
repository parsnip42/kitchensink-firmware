#include "usbkeyboard.h"

#include "usb_keyboard.h"

UsbKeyboard::UsbKeyboard()
{
    clear();
}

void UsbKeyboard::setKey(int keyId)
{
    if (mKeyNum < 6)
    {
        keyboard_keys[mKeyNum++] = keyId;
    }
}

void UsbKeyboard::setModifier(int modifierId)
{
    keyboard_modifier_keys |= modifierId;
}

void UsbKeyboard::send()
{
    usb_keyboard_send();
    clear();
}

void UsbKeyboard::clear()
{
    mKeyNum = 0;
    
    keyboard_modifier_keys = 0;
    keyboard_keys[0] = 0;
    keyboard_keys[1] = 0;
    keyboard_keys[2] = 0;
    keyboard_keys[3] = 0;
    keyboard_keys[4] = 0;
    keyboard_keys[5] = 0;
}
