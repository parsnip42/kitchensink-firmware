#include "ledsource.h"

#include "event/ledmaskevent.h"
#include "event/eventstage.h"

#include <usb_keyboard.h>

LedSource::LedSource()
    : mMaskValue(0)
{ }

void LedSource::pollEvent(EventStage& next)
{
    if (keyboard_leds != mMaskValue)
    {
        mMaskValue = keyboard_leds;
        
        next.processEvent(LedMaskEvent::create(mMaskValue));
    }
}











