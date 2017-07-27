#ifndef INCLUDED_SMARTKEYSET_H
#define INCLUDED_SMARTKEYSET_H

#include "smartkey.h"
#include "config.h"

#include <array>

typedef std::array<SmartKey, Config::kSmartKeyCount> SmartKeySet;

#endif
