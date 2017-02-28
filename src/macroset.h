#ifndef INCLUDED_MACROSET_H
#define INCLUDED_MACROSET_H

#include "arraypool.h"
#include "keyevent.h"
#include "macrotype.h"
#include "poolindexentry.h"
#include "types/strref.h"
#include "types/strbuf.h"

#include <array>
#include <initializer_list>

class MacroSet
{
public:
    class Entry
    {
    public:
        constexpr Entry();

    public:
        MacroType         type;
        Types::StrBuf<24> name;
    };
    
private:
    typedef std::array<KeyEvent, 1024>            Pool;
    typedef PoolIndexEntry<Pool::iterator, Entry> PoolEntry;
    typedef std::array<PoolEntry, 30>             Index;
    typedef ArrayPool<Pool, Index>                MacroPool;

public:
    typedef MacroPool::Entry Macro;

public:
    constexpr MacroSet() = default;
    
public:
    constexpr std::size_t size() const;
    
    template <typename Iterator>
    void setMacro(std::size_t          index,
                  const MacroType&     type,
                  const Types::StrRef& name,
                  const Iterator&      begin,
                  const Iterator&      end);
    
    void setMacro(std::size_t                            index,
                  const MacroType&                       type,
                  const std::initializer_list<KeyEvent>& press);
    
    void setMacro(std::size_t                            index,
                  const MacroType&                       type,
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
constexpr MacroSet::Entry::Entry()
    : type(MacroType::kSync)
{ }


inline
constexpr std::size_t MacroSet::size() const
{
    return mMacroPool.size();
}

template <typename Iterator>
inline
void MacroSet::setMacro(std::size_t          index,
                        const MacroType&     type,
                        const Types::StrRef& name,
                        const Iterator&      begin,
                        const Iterator&      end)
{
    auto& data(mMacroPool[index].data);

    data.type = type;
    data.name = name;
    
    mMacroPool.insert(index, begin, end);
}

inline
void MacroSet::setMacro(std::size_t                            index,
                        const MacroType&                       type,
                        const std::initializer_list<KeyEvent>& press)
{
    setMacro(index, type, "", press.begin(), press.end());
}

inline
void MacroSet::setMacro(std::size_t                            index,
                        const MacroType&                       type,
                        const Types::StrRef&                   name,
                        const std::initializer_list<KeyEvent>& press)
{
    setMacro(index, type, name, press.begin(), press.end());
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
