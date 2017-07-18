#ifndef INCLUDED_MACROSET_H
#define INCLUDED_MACROSET_H

#include "keyevent.h"
#include "macro.h"
#include "macrotype.h"
#include "macrodatapool.h"
#include "types/strref.h"
#include "types/strbuf.h"

#include <array>
#include <initializer_list>

class MacroSet
{
private:
    typedef std::array<Macro, 30> MacroData;

public:
    MacroSet();
    
public:
    std::size_t size() const;
    
    template <typename Iterator>
    void setMacro(std::size_t      index,
                  const MacroType& type,
                  const StrRef&    name,
                  const Iterator&  begin,
                  const Iterator&  end);
    
    void setMacro(std::size_t                            index,
                  const MacroType&                       type,
                  const StrRef&                          name,
                  const std::initializer_list<KeyEvent>& press);

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


template <typename Iterator>
inline
void MacroSet::setMacro(std::size_t      index,
                        const MacroType& type,
                        const StrRef&    name,
                        const Iterator&  begin,
                        const Iterator&  end)
{
    auto& macro(mMacroData[index]);

    macro.type = type;
    macro.name = name;
    macro.setContent(begin, end);
}

inline
std::size_t MacroSet::size() const
{
    return mMacroPool.size();
}

inline
void MacroSet::setMacro(std::size_t                            index,
                        const MacroType&                       type,
                        const StrRef&                          name,
                        const std::initializer_list<KeyEvent>& press)
{
    setMacro(index, type, name, press.begin(), press.end());
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
