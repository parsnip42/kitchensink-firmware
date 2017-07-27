#ifndef INCLUDED_MACROSET_H
#define INCLUDED_MACROSET_H

#include "keyevent.h"
#include "macro.h"
#include "macrotype.h"
#include "macrodatapool.h"
#include "types/strref.h"
#include "types/strbuf.h"
#include "config.h"

#include <array>
#include <initializer_list>

class MacroSet
{
private:
    typedef std::array<Macro, Config::kMacroCount> MacroData;

public:
    MacroSet();
    
public:
    std::size_t size() const;

private:
    MacroDataPool mMacroPool;
    MacroData     mMacroData;
    
public:
    const Macro& operator[](std::size_t index) const;
    Macro& operator[](std::size_t index);

private:
    MacroSet(const MacroSet&) = delete;
    MacroSet& operator=(const MacroSet&) = delete;
};


inline
std::size_t MacroSet::size() const
{
    return mMacroPool.size();
}

inline
const Macro& MacroSet::operator[](std::size_t index) const
{
    return mMacroData[index];
}

inline
Macro& MacroSet::operator[](std::size_t index)
{
    return mMacroData[index];
}

#endif
