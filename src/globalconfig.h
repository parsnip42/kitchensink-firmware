#ifndef INCLUDED_GLOBALCONFIG_H
#define INCLUDED_GLOBALCONFIG_H

#include <cstdint>

#include "homeledset.h"

class GlobalConfig
{
public:
    GlobalConfig();

public:
    uint32_t   tapDelay;
    uint32_t   keyRepeatDelay;
    uint32_t   keyRepeatRate;
    uint32_t   homeScreenColumns;
    uint32_t   homeScreenTimeout;
    HomeLedSet homeLedSet;

private:
    GlobalConfig(const GlobalConfig&);
    GlobalConfig& operator=(const GlobalConfig&);
};

#endif
