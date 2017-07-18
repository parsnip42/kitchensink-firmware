#ifndef INCLUDED_MACRO_H
#define INCLUDED_MACRO_H

#include "macrotype.h"
#include "macrodatapool.h"
#include "types/range.h"
#include "types/strbuf.h"

#include <array>
#include <algorithm>

class Macro
{
public:
    typedef Range<MacroDataPool::const_iterator> Content;

public:
    Macro() = default;
    Macro(MacroDataPool* dataPool,
          std::size_t    index);

public:
    Content content() const;
    void setContent(MacroDataPool::const_iterator begin,
                    MacroDataPool::const_iterator end);

public:
    MacroType  type;
    StrBuf<24> name;
    StrBuf<24> shortcut;

public:
    MacroDataPool* mDataPool;
    std::size_t    mIndex;
};


inline
Macro::Macro(MacroDataPool* dataPool,
             std::size_t    index)
    : mDataPool(dataPool)
    , mIndex(index)
{ }

inline
Macro::Content Macro::content() const
{
    return (*mDataPool)[mIndex];
}

inline
void Macro::setContent(MacroDataPool::const_iterator begin,
                       MacroDataPool::const_iterator end)
{
    mDataPool->insert(mIndex, begin, end);
}

#endif /* INCLUDED_MACRO_H */
