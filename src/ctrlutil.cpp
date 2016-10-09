#include "ctrlutil.h"

#include <core_pins.h>

extern "C" char* sbrk(int incr);

namespace CtrlUtil
{

void bootloader()
{
    _reboot_Teensyduino_();
}

std::size_t freeMemory()
{
    // http://forum.pjrc.com/threads/23256-Get-Free-Memory-for-Teensy-3-0

    char top;
    return &top - reinterpret_cast<char*>(sbrk(0));
}

}
