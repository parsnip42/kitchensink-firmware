#ifndef INCLUDED_MODIFIERSET_H
#define INCLUDED_MODIFIERSET_H

#include "modifier.h"

#include <array>

class ModifierSet
{
public:
    enum Type
    {
        kLeftShift = 1
    };
    
public:
    ModifierSet();

public:
    void processKeyPress();
    
public:
    Modifier& operator[](Type type);
    
private:
    std::array<Modifier, 10> mModifiers; 
};

#endif
