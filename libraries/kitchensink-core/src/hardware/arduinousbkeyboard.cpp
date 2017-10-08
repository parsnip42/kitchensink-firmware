#ifndef TEENSYDUINO




#include "hardware/arduinousbkeyboard.h"

#include "event/keyevent.h"
#include "data/keycodeutil.h"

#include <HID.h>

#include <cstring>

namespace
{

// Taken from standard Arduino Keyboard.cpp
const uint8_t hidReportDescriptor[] =
{
  //  Keyboard
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 47
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
   
  0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    
  0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    
  0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    
  0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                          // END_COLLECTION
};

}

ArduinoUsbKeyboard::ArduinoUsbKeyboard()
    : mKeyNum(0)
    , mDirty(false)
{
    static HIDSubDescriptor node(hidReportDescriptor, sizeof(hidReportDescriptor));
    
    HID().AppendDescriptor(&node);

    std::memset(mKeyMask, 0, sizeof(mKeyMask));
    std::memset(&mKeyReport, 0, sizeof(mKeyReport));
}

bool ArduinoUsbKeyboard::processEvent(const Event& event)
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
                HID().SendReport(2, &mKeyReport, sizeof(mKeyReport));
                mDirty = false;
            }
        }
        
        return true;
    }

    return false;
}

void ArduinoUsbKeyboard::pressKey(KeyCode key)
{
    auto keyCode(static_cast<size_t>(key));
    
    if (!(mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7))))
    {
        if (KeyCodeUtil::modifier(key))
        {
            mKeyReport.modifiers |= (1 << KeyCodeUtil::modifierIndex(key));
            mDirty = true;
        }
        else if (mKeyNum < 6)
        {
            mKeyReport.keys[mKeyNum++] = keyCode;
            mDirty = true;
        }
        
        mKeyMask[keyCode >> 3] |= (1 << (keyCode & 0x7));
    }
}

void ArduinoUsbKeyboard::releaseKey(KeyCode key)
{
    auto keyCode(static_cast<size_t>(key));

    if (mKeyMask[keyCode >> 3] & (1 << (keyCode & 0x7)))
    {
        if (KeyCodeUtil::modifier(key))
        {
            mKeyReport.modifiers &= ~(1 << KeyCodeUtil::modifierIndex(key));
            mDirty = true;
        }
        else
        {
            for (int i = 0; i < mKeyNum; ++i)
            {
                if (mKeyReport.keys[i] == keyCode)
                {
                    mKeyReport.keys[i] = mKeyReport.keys[--mKeyNum];
                    mKeyReport.keys[mKeyNum] = 0;
                    mDirty = true;
                    break;
                }
            }
        }
        
        mKeyMask[keyCode >> 3] &= ~(1 << (keyCode & 0x7));
    }
}


#endif
