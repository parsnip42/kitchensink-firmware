#include "bluefruitkeyboard.h"

#include "event/keyevent.h"
#include "data/keycodeutil.h"

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#include <cstring>

namespace
{
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
}

BluefruitKeyboard::BluefruitKeyboard()
    : mModifiers(0)
    , mKeyNum(0)
    , mDirty(false)
{
    mKeys.fill(0);
    std::memset(mKeyMask, 0, sizeof(mKeyMask));

    ble.begin();
    
    ble.echo(false);
    ble.sendCommandCheckOK(F("AT+GAPDEVNAME=kitchenSink keyboard"));
    ble.sendCommandCheckOK(F("AT+BleHIDEn=On"));

    ble.reset();
}

bool BluefruitKeyboard::processEvent(const Event& event)
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
                update();
                mDirty = false;
            }
        }
        
        return true;
    }

    return false;
}

void BluefruitKeyboard::pressKey(KeyCode key)
{
    auto keyCode(static_cast<size_t>(key));
    
    if (!(mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7))))
    {
        if (KeyCodeUtil::modifier(key))
        {
            mModifiers |= (1 << KeyCodeUtil::modifierIndex(key));
            mDirty = true;
        }
        else if (mKeyNum < 6)
        {
            mKeys[mKeyNum++] = keyCode;
            mDirty = true;
        }
        
        mKeyMask[keyCode >> 3] |= (1 << (keyCode & 0x7));
    }
}

void BluefruitKeyboard::releaseKey(KeyCode key)
{
    auto keyCode(static_cast<size_t>(key));

    if (mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7)))
    {
        if (KeyCodeUtil::modifier(key))
        {
            mModifiers &= ~(1 << KeyCodeUtil::modifierIndex(key));
            mDirty = true;
        }
        else
        {
            for (int i = 0; i < mKeyNum; ++i)
            {
                if (mKeys[i] == keyCode)
                {
                    mKeys[i] = mKeys[--mKeyNum];
                    mKeys[mKeyNum] = 0;
                    mDirty = true;
                    break;
                }
            }
        }
        
        mKeyMask[keyCode >> 3] &= ~(1 << (keyCode & 0x7));
    }
}

void BluefruitKeyboard::update()
{
    char atStr[64];
            
    snprintf(atStr, sizeof(atStr), "AT+BLEKEYBOARDCODE=%2.2x-00-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x-%2.2x",
             mModifiers, mKeys[0], mKeys[1], mKeys[2], mKeys[3], mKeys[4], mKeys[5]);
            
    ble.println(atStr);

}
