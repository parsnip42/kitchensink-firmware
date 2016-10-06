#include "modifierset.h"

ModifierSet::ModifierSet()
{ }

Modifier& ModifierSet::operator[](uint8_t type)
{
    return mModifiers[type];
}
