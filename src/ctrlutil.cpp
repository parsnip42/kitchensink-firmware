#include "ctrlutil.h"

#include <core_pins.h>

namespace CtrlUtil
{

void bootloader()
{
    _reboot_Teensyduino_();
}

}
