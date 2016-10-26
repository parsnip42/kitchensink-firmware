#ifndef INCLUDED_MODIFIERSET_H
#define INCLUDED_MODIFIERSET_H

#include "modifier.h"

#include <array>

class ModifierSet
{
public:
    ModifierSet();

public:
    Modifier& operator[](uint8_t modifier);
    
private:
    std::array<Modifier, 30> mModifiers;
};


inline
ModifierSet::ModifierSet()
{ }

inline
Modifier& ModifierSet::operator[](uint8_t modifier)
{
    return mModifiers[modifier];
}

#endif
