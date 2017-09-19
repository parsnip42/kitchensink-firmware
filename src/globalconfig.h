#ifndef INCLUDED_GLOBALCONFIG_H
#define INCLUDED_GLOBALCONFIG_H

#include <cstdint>

class GlobalConfig
{
public:
    GlobalConfig();

public:
    uint32_t tapDelay;
    uint32_t keyRepeatDelay;
    uint32_t keyRepeatRate;
};

#endif
