#ifndef INCLUDED_MACROSET_H
#define INCLUDED_MACROSET_H

#include "arraypool.h"
#include "keyevent.h"
#include "types/strref.h"
#include "types/strbuf.h"
#include "poolindexentry.h"

#include <array>
#include <initializer_list>

class MacroSet
{
private:
    typedef std::array<KeyEvent, 1024>                         Pool;
    typedef PoolIndexEntry<Pool::iterator, Types::StrBuf<24> > PoolEntry;
    typedef std::array<PoolEntry, 30>                          Index;
    typedef ArrayPool<Pool, Index>                             MacroPool;

public:
    typedef MacroPool::Entry Macro;

public:
    constexpr MacroSet() = default;
    
public:
    constexpr std::size_t size() const;
    
    template <typename Iterator>
    void setMacro(std::size_t     index,
                  const Iterator& begin,
                  const Iterator& end);
    
    void setMacro(std::size_t                            index,
                  const std::initializer_list<KeyEvent>& press);
    
    void setMacro(std::size_t                            index,
                  const Types::StrRef&                   name,
                  const std::initializer_list<KeyEvent>& press);

private:
    MacroPool mMacroPool;
    
public:
    const Macro& operator[](int index) const;
    Macro& operator[](int index);
    
private:
    MacroSet(const MacroSet&) = delete;
    MacroSet& operator=(const MacroSet&) = delete;
};


inline
constexpr std::size_t MacroSet::size() const
{
    return mMacroPool.size();
}

template <typename Iterator>
inline
void MacroSet::setMacro(std::size_t     index,
                        const Iterator& begin,
                        const Iterator& end)
{
    mMacroPool.insert(index, begin, end);
}

inline
void MacroSet::setMacro(std::size_t index, const std::initializer_list<KeyEvent>& press)
{
    setMacro(index, press.begin(), press.end());
}

inline
void MacroSet::setMacro(std::size_t                            index,
                        const Types::StrRef&                   name,
                        const std::initializer_list<KeyEvent>& press)
{
    setMacro(index, press.begin(), press.end());
    mMacroPool[index].data = name;
}

inline
const MacroSet::Macro& MacroSet::operator[](int index) const
{
    return mMacroPool[index];
}

inline
MacroSet::Macro& MacroSet::operator[](int index)
{
    return mMacroPool[index];
}

#endif
