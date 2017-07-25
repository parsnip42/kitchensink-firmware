#include "keyeventpipeline.h"

#include <elapsedMillis.h>

uint32_t KeyEventPipeline::nowMs() const
{
    return millis();
}
