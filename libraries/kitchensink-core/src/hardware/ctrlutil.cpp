#include "hardware/ctrlutil.h"

#include <Arduino.h>

#ifdef TEENSYDUINO
#include <core_pins.h>
#endif

extern "C" char* sbrk(int incr);

namespace CtrlUtil
{

void bootloader()
{
    #ifdef TEENSYDUINO
    _reboot_Teensyduino_();
    #endif
}

std::size_t freeMemory()
{
    // http://forum.pjrc.com/threads/23256-Get-Free-Memory-for-Teensy-3-0

    char top;
    return &top - reinterpret_cast<char*>(sbrk(0));
}

uint32_t nowMs()
{
    return millis();
}

}
