#include "usbkeyboard.h"

#include <usb_keyboard.h>
#include <cstring>

UsbKeyboard::UsbKeyboard()
    : mKeyNum(0)
    , mDirty(false)
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

void UsbKeyboard::processKey(uint8_t keyCode, KeyState state)
{
    if (state == KeyState::kPressed)
    {
        pressKey(keyCode);
    }
    else if (state == KeyState::kReleased)
    {
        releaseKey(keyCode);
    }
}

void UsbKeyboard::processModifier(uint8_t modifier, KeyState state)
{
    uint8_t active(state == KeyState::kPressed);
    uint8_t set(active << modifier);
    uint8_t clear(~(1 << modifier));
    
    auto nextMask((keyboard_modifier_keys & clear) | set);

    if (nextMask != keyboard_modifier_keys)
    {
        keyboard_modifier_keys = nextMask;
        mDirty = true;
    }
}

void UsbKeyboard::update()
{
    if (mDirty)
    {
        usb_keyboard_send();
        mDirty = false;
    }
}

void UsbKeyboard::pressKey(uint8_t keyCode)
{
    if (!(mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7)))
         && (mKeyNum < 6))
    {
        keyboard_keys[mKeyNum++] = keyCode;
        mKeyMask[keyCode >> 3] |= (1 << (keyCode & 0x7));
        mDirty = true;
    }
}

void UsbKeyboard::releaseKey(uint8_t keyCode)
{
    for (int i = 0; i < mKeyNum; ++i)
    {
        if (keyboard_keys[i] == keyCode)
        {
            keyboard_keys[i] = keyboard_keys[--mKeyNum];
            keyboard_keys[mKeyNum] = 0;
            mKeyMask[keyCode >> 3] &= ~(1 << (keyCode & 0x7));
            mDirty = true;
            break;
        }
    }
}
