#ifndef INCLUDED_PROFILE_H
#define INCLUDED_PROFILE_H

#include "macroset.h"
#include "modifierset.h"

class Profile
{
public:
    constexpr Profile() = default;

public:
    MacroSet    macroSet;
    ModifierSet modifierSet;
    
private:
    Profile(const Profile&);
    Profile& operator=(const Profile&);
};

#endif
