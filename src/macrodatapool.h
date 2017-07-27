#ifndef INCLUDED_MACRODATAPOOL_H
#define INCLUDED_MACRODATAPOOL_H

#include "keyevent.h"
#include "types/arraypool.h"
#include "config.h"

#include <array>

class MacroDataPool : public ArrayPool<std::array<KeyEvent, Config::kMacroPoolSize>, Config::kMacroCount>
{
public:
    MacroDataPool() = default;

private:
    MacroDataPool(const MacroDataPool&);
    MacroDataPool& operator=(const MacroDataPool&);
};

#endif
