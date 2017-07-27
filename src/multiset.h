#ifndef INCLUDED_MULTISET_H
#define INCLUDED_MULTISET_H

#include "multi.h"
#include "config.h"

#include <array>

typedef std::array<Multi, Config::kMultiKeyCount> MultiSet;

#endif
