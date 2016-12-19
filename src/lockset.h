#ifndef INCLUDED_LOCKSET_H
#define INCLUDED_LOCKSET_H

#include "lock.h"

#include <array>

typedef std::array<Lock, 30> LockSet;

#endif
