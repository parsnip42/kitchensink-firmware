#ifndef INCLUDED_MACROSET_H
#define INCLUDED_MACROSET_H

#include "arraypool.h"
#include "keyevent.h"

#include <array>
#include <initializer_list>

class MacroSet
{
public:
    constexpr MacroSet() = default;
    
public:
    void setMacro(int index, const std::initializer_list<KeyEvent>& press);

private:
    typedef ArrayPool<std::array<KeyEvent, 1024>, 20> MacroPool;
    
    MacroPool mMacroPool;
    
public:
    class Macro
    {
    public:
        Macro(const MacroSet&            macroSet,
              MacroSet::MacroPool::Entry entry)
            : mMacroSet(macroSet)
            , mEntry(entry)
        { }
        
    public:
        typedef MacroPool::const_iterator         const_iterator;
        typedef MacroPool::const_reverse_iterator const_reverse_iterator;

        const_iterator begin()
        {
            return mMacroSet.mMacroPool.begin() + mEntry.begin;
        }

        const_iterator end()
        {
            return mMacroSet.mMacroPool.begin() + mEntry.end;
        }

        const_reverse_iterator rbegin()
        {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend()
        {
            return const_reverse_iterator(begin());
        }
        

    private:
        const MacroSet&            mMacroSet;
        MacroSet::MacroPool::Entry mEntry;
    };
    
    Macro operator[](int index) const;
    
private:
    MacroSet(const MacroSet&) = delete;
    MacroSet& operator=(const MacroSet&) = delete;
};


inline
MacroSet::Macro MacroSet::operator[](int index) const
{
    return Macro(*this, mMacroPool[index]);
}

#endif
