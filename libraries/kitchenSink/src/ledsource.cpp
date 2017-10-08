#include "ledsource.h"

#include "event/ledmaskevent.h"
#include "event/eventstage.h"

#ifdef TEENSYDUINO
#include <usb_keyboard.h>
#else

// Nop for now.
namespace
{
const uint8_t keyboard_leds = 0;
}

#endif


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
