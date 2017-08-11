#include "ledsource.h"

#include "keyevent.h"
#include "keyeventstage.h"

#include <usb_keyboard.h>

LedSource::LedSource()
    : mMaskValue(0)
{ }

void LedSource::pollKeyEvent(KeyEventStage& next)
{
    if (keyboard_leds != mMaskValue)
    {
        mMaskValue = keyboard_leds;
        
        next.processKeyEvent(KeyEvent(KeyId::LedMask(mMaskValue)));
    }
}











