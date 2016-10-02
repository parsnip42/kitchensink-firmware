#ifndef INCLUDED_MODIFIERSET_H
#define INCLUDED_MODIFIERSET_H

#include "modifier.h"
#include "modifierid.h"

#include <array>

class ModifierSet
{
public:
    ModifierSet();

public:
    void processKeyPress();
    
public:
    Modifier& operator[](const ModifierId& type);
    Modifier& operator[](uint8_t type);

private:
    std::array<Modifier, 10> mModifiers; 
};

#endif
