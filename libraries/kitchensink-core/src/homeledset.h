#ifndef INCLUDED_HOMELEDSET_H
#define INCLUDED_HOMELEDSET_H

#include "homeled.h"
#include "config.h"

#include <array>

typedef std::array<HomeLed, Config::kHomeLedCount> HomeLedSet;

#endif
