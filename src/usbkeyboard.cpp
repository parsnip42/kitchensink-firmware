#include "usbkeyboard.h"

#include "keyevent.h"
#include "data/keycodes.h"

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

void UsbKeyboard::processKeyEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);
    
    if (keyId.type() == KeyId::Type::kKey
        && keyId.value() != 0)
    {
        auto keyCode(keyId.value());
    
        if (event.pressed)
        {
            pressKey(keyCode);
        }
        else
        {
            releaseKey(keyCode);
        }
        
        if (mDirty)
        {
            usb_keyboard_send();
            mDirty = false;
        }
    }
}

void UsbKeyboard::pressKey(uint8_t keyCode)
{
    if (!(mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7))))
    {
        if (keyCode >= KeyCodes::ModifierOffset)
        {
            keyboard_modifier_keys |= (1 << (keyCode - KeyCodes::ModifierOffset));
            mDirty = true;
        }
        else if (mKeyNum < 6)
        {
            keyboard_keys[mKeyNum++] = keyCode;
            mDirty = true;
        }
        
        mKeyMask[keyCode >> 3] |= (1 << (keyCode & 0x7));
    }
}

void UsbKeyboard::releaseKey(uint8_t keyCode)
{
    if (mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7)))
    {
        if (keyCode >= KeyCodes::ModifierOffset)
        {
            keyboard_modifier_keys &= ~(1 << (keyCode - KeyCodes::ModifierOffset));
            mDirty = true;
        }
        else
        {
            for (int i = 0; i < mKeyNum; ++i)
            {
                if (keyboard_keys[i] == keyCode)
                {
                    keyboard_keys[i] = keyboard_keys[--mKeyNum];
                    keyboard_keys[mKeyNum] = 0;
                    mDirty = true;
                    break;
                }
            }
        }
        
        mKeyMask[keyCode >> 3] &= ~(1 << (keyCode & 0x7));
    }
}
