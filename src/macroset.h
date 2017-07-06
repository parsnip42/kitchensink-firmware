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
private:
    typedef std::array<KeyEvent, 1024> Pool;
    typedef ArrayPool<Pool, 30>        MacroPool;

    class MacroData
    {
    public:
        MacroType  type;
        StrBuf<24> name;
    };

    typedef std::array<MacroData, 30>  Index;

public:
    class Macro
    {
    public:
        typedef Range<MacroPool::const_iterator> Content;
        
    private:
        Macro(const Index&     index,
              const MacroPool& pool,
              std::size_t      n);

    public:
        StrRef name() const;
        MacroType type() const;
        Content content() const;
        
    private:
        const Index&     mIndex;
        const MacroPool& mPool;
        std::size_t      mN;

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
                  const std::initializer_list<KeyEvent>& press);
    
    void setMacro(std::size_t                            index,
                  const MacroType&                       type,
                  const StrRef&                          name,
                  const std::initializer_list<KeyEvent>& press);
    

private:
    Index     mIndex;
    MacroPool mMacroPool;
    
public:
    const Macro operator[](int index) const;
    Macro operator[](int index);
    
private:
    MacroSet(const MacroSet&) = delete;
    MacroSet& operator=(const MacroSet&) = delete;
};


inline
MacroSet::Macro::Macro(const Index&     index,
                       const MacroPool& pool,
                       std::size_t      n)
    : mIndex(index)
    , mPool(pool)
    , mN(n)
{ }

inline
StrRef MacroSet::Macro::name() const
{
    return mIndex[mN].name;
}

inline
MacroType MacroSet::Macro::type() const
{
    return mIndex[mN].type;
}

inline
MacroSet::Macro::Content MacroSet::Macro::content() const
{
    return mPool[mN];
}


template <typename Iterator>
inline
void MacroSet::setMacro(std::size_t      index,
                        const MacroType& type,
                        const StrRef&    name,
                        const Iterator&  begin,
                        const Iterator&  end)
{
    auto& macro(mIndex[index]);

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
                        const std::initializer_list<KeyEvent>& press)
{
    setMacro(index, type, "", press.begin(), press.end());
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
    return Macro(mIndex, mMacroPool, index); 
}

inline
MacroSet::Macro MacroSet::operator[](int index)
{
    return Macro(mIndex, mMacroPool, index); 
}

#endif
