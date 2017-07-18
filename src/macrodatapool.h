#ifndef INCLUDED_MACRODATAPOOL_H
#define INCLUDED_MACRODATAPOOL_H

#include "keyevent.h"
#include "types/arraypool.h"

#include <array>

class MacroDataPool : public ArrayPool<std::array<KeyEvent, 1024>, 30>
{
public:
    MacroDataPool() = default;

private:
    MacroDataPool(const MacroDataPool&);
    MacroDataPool& operator=(const MacroDataPool&);
};

#endif /* INCLUDED_MACRODATAPOOL_H */
