#include "modifierset.h"

ModifierSet::ModifierSet()
{ }

Modifier& ModifierSet::operator[](Type type)
{
    return mModifiers[type];
}
