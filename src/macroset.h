#ifndef INCLUDED_MACROSET_H
#define INCLUDED_MACROSET_H

#include "keyevent.h"
#include "macrotype.h"
#include "types/arraypool.h"
#include "types/strref.h"
#include "types/strbuf.h"

#include <array>
#include <initializer_list>

class MacroSet
{
private:
    typedef std::array<KeyEvent, 1024> PoolData;
    typedef ArrayPool<PoolData, 30>    MacroPool;

    class MacroDataEntry
    {
    public:
        MacroType  type;
        StrBuf<24> name;
        StrBuf<24> shortcut;
    };

    typedef std::array<MacroDataEntry, 30> MacroData;

public:
    class Macro
    {
    public:
        typedef Range<MacroPool::const_iterator> Content;
        
    private:
        Macro(const MacroData& data,
              const MacroPool& pool,
              std::size_t      index);

    public:
        StrRef name() const;
        MacroType type() const;
        Content content() const;
        
    private:
        const MacroData& mData;
        const MacroPool& mPool;
        std::size_t      mIndex;

    private:
        friend class MacroSet;
    };
    
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
    MacroData mMacroData;
    MacroPool mMacroPool;
    
public:
    const Macro operator[](int index) const;
    
private:
    MacroSet(const MacroSet&) = delete;
    MacroSet& operator=(const MacroSet&) = delete;
};


inline
MacroSet::Macro::Macro(const MacroData& data,
                       const MacroPool& pool,
                       std::size_t      index)
    : mData(data)
    , mPool(pool)
    , mIndex(index)
{ }

inline
StrRef MacroSet::Macro::name() const
{
    return mData[mIndex].name;
}

inline
MacroType MacroSet::Macro::type() const
{
    return mData[mIndex].type;
}

inline
MacroSet::Macro::Content MacroSet::Macro::content() const
{
    return mPool[mIndex];
}


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
    
    mMacroPool.insert(index, begin, end);
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
const MacroSet::Macro MacroSet::operator[](int index) const
{
    return Macro(mMacroData, mMacroPool, index); 
}

#endif
