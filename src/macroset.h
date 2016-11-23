#ifndef INCLUDED_MACROSET_H
#define INCLUDED_MACROSET_H

#include "arraypool.h"
#include "keyevent.h"

#include <array>
#include <initializer_list>

class MacroSet
{
private:
    typedef ArrayPool<std::array<KeyEvent, 1024>, 20> MacroPool;

public:
    class Macro
    {
    public:
        typedef MacroPool::const_iterator         const_iterator;
        typedef MacroPool::const_reverse_iterator const_reverse_iterator;

    public:
        constexpr Macro(const MacroSet&            macroSet,
                        MacroSet::MacroPool::Entry entry);
        
    public:
        const_iterator begin() const;
        const_iterator end() const;

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;        

    private:
        const MacroSet&            mMacroSet;
        MacroSet::MacroPool::Entry mEntry;
    };

public:
    constexpr MacroSet() = default;
    
public:
    void setMacro(int index, const std::initializer_list<KeyEvent>& press);
    std::size_t size() const;
    
private:
    MacroPool mMacroPool;
    
public:
    Macro operator[](int index) const;
    
private:
    MacroSet(const MacroSet&) = delete;
    MacroSet& operator=(const MacroSet&) = delete;
};


inline
constexpr MacroSet::Macro::Macro(const MacroSet&            macroSet,
                                 MacroSet::MacroPool::Entry entry)
    : mMacroSet(macroSet)
    , mEntry(entry)
{ }

inline
std::size_t MacroSet::size() const
{
    return mMacroPool.size();
}

inline
MacroSet::Macro::const_iterator MacroSet::Macro::begin() const
{
    return mMacroSet.mMacroPool.begin() + mEntry.begin;
}

inline
MacroSet::Macro::const_iterator MacroSet::Macro::end() const
{
    return mMacroSet.mMacroPool.begin() + mEntry.end;
}

inline
MacroSet::Macro::const_reverse_iterator MacroSet::Macro::rbegin() const
{
    return const_reverse_iterator(end());
}

inline
MacroSet::Macro::const_reverse_iterator MacroSet::Macro::rend() const
{
    return const_reverse_iterator(begin());
}


inline
MacroSet::Macro MacroSet::operator[](int index) const
{
    return Macro(*this, mMacroPool[index]);
}

#endif
