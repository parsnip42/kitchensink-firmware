#include "usbkeyboard.h"

#include "event/keyevent.h"
#include "data/keycodeutil.h"

#ifdef TEENSYDUINO
#include <usb_keyboard.h>
#else
#include <Keyboard.h>
#endif

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

bool UsbKeyboard::processEvent(const Event& event)
{
    if (event.is<KeyEvent>())
    {
        auto keyEvent(event.get<KeyEvent>());
        auto key(keyEvent.key);
        
        if (key != KeyCode::None)
        {
            if (keyEvent.pressed)
            {
                pressKey(key);
            }
            else
            {
                releaseKey(key);
            }
            
            if (mDirty)
            {
                usb_keyboard_send();
                mDirty = false;
            }
        }
        
        return true;
    }

    return false;
}

void UsbKeyboard::pressKey(KeyCode key)
{
    auto keyCode(static_cast<size_t>(key));
    
    if (!(mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7))))
    {
        if (KeyCodeUtil::modifier(key))
        {
            keyboard_modifier_keys |= (1 << KeyCodeUtil::modifierIndex(key));
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

void UsbKeyboard::releaseKey(KeyCode key)
{
    auto keyCode(static_cast<size_t>(key));

    if (mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7)))
    {
        if (KeyCodeUtil::modifier(key))
        {
            keyboard_modifier_keys &= ~(1 << KeyCodeUtil::modifierIndex(key));
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
