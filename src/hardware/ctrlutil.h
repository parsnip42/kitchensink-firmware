#ifndef INCLUDED_CTRLUTIL_H
#define INCLUDED_CTRLUTIL_H

#include <cstdint>

namespace CtrlUtil
{

void bootloader();
std::size_t freeMemory();

}

#endif
