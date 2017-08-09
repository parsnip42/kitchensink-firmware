#ifndef INCLUDED_KEYMASK_H
#define INCLUDED_KEYMASK_H

#include "types/bitmask2d.h"
#include "config.h"

typedef Bitmask2d<Config::kLayerColumns, Config::kLayerRows> KeyMask;

#endif
