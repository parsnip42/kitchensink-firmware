#include "teensyledsource.h"

#include "event/ledmaskevent.h"
#include "event/eventstage.h"

#include <usb_keyboard.h>

TeensyLedSource::TeensyLedSource()
    : mMaskValue(0)
{ }

void TeensyLedSource::pollEvent(EventStage& next)
{
    if (keyboard_leds != mMaskValue)
    {
        mMaskValue = keyboard_leds;
        
        next.processEvent(LedMaskEvent::create(mMaskValue));
    }
}
