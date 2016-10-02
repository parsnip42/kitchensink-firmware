#include "modifierset.h"

ModifierSet::ModifierSet()
{ }

Modifier& ModifierSet::operator[](const ModifierId& type)
{
    return mModifiers[type.value()];
}

Modifier& ModifierSet::operator[](uint8_t type)
{
    return mModifiers[type];
}
