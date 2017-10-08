#ifndef INCLUDED_MULTIKEYSET_H
#define INCLUDED_MULTIKEYSET_H

#include "multikey.h"
#include "config.h"

#include <array>

typedef std::array<MultiKey, Config::kMultiKeyCount> MultiKeySet;

#endif
