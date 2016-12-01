#include "timed.h"

#include <elapsedMillis.h>

namespace TimedImpl
{

uint32_t nowMs()
{
    return millis();
}

void delayMs(uint32_t ms)
{
    delay(ms);
}

}
