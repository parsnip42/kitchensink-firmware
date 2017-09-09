#ifndef INCLUDED_MACRODATAPOOL_H
#define INCLUDED_MACRODATAPOOL_H

#include "event/event.h"
#include "types/arraypool.h"
#include "config.h"

#include <array>

class MacroDataPool : public ArrayPool<std::array<Event, Config::kMacroPoolSize>, Config::kMacroCount>
{
public:
    MacroDataPool() = default;
};

#endif
