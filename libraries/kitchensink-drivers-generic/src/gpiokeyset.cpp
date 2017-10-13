#include "gpiokeyset.h"

#ifdef TEENSYDUINO
#include <core_pins.h>
#else
#include <Arduino.h>
#undef min
#undef max
#endif

GPIOKeySet::GPIOKeySet(const_iterator pinsBegin,
                       const_iterator pinsEnd)
    : mPins(pinsBegin, pinsEnd)
{
    for (auto pin : mPins)
    {
        pinMode(pin, INPUT);
        digitalWrite(pin, HIGH);
    }
}

bool GPIOKeySet::readPin(uint8_t pin) const
{
    return !digitalRead(pin);
}
