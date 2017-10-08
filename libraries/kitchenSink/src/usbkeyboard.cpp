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
#ifdef TEENSYDUINO
                usb_keyboard_send();
#endif
                mDirty = false;
            }
        }
        
        return true;
    }

    return false;
}

void UsbKeyboard::pressKey(KeyCode key)
{
#ifdef TEENSYDUINO

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

#endif
}

void UsbKeyboard::releaseKey(KeyCode key)
{
#ifdef TEENSYDUINO

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

#endif TEENSYDUINO
}
