#include "eventmanager.h"

#include <elapsedMillis.h>

uint32_t EventManager::nowMs() const
{
    return millis();
}
