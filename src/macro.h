#ifndef INCLUDED_MACRO_H
#define INCLUDED_MACRO_H

#include "macrotype.h"
#include "macrodatapool.h"
#include "types/strbuf.h"
#include "config.h"

#include <array>
#include <algorithm>

class Macro
{
public:
    class Content
    {
    private:
        Content() = default;
        Content(MacroDataPool* dataPool,
                std::size_t    index);
        
    public:
        typedef MacroDataPool::const_iterator const_iterator;

    public:
        const_iterator begin() const;
        const_iterator end() const;
        
        void assign(const_iterator begin,
                    const_iterator end);

        Content& operator=(const std::initializer_list<Event>& data);
        
    private:
        MacroDataPool* mDataPool;
        std::size_t    mIndex;

    private:
        friend class Macro;
    };
    
public:
    Macro() = default;
    Macro(MacroDataPool* dataPool,
          std::size_t    index);

public:
    MacroType                         type;
    StrBuf<Config::kMacroNameLen>     name;
    StrBuf<Config::kMacroShortcutLen> shortcut;
    Content                           content;
};


inline
Macro::Content::Content(MacroDataPool* dataPool,
                        std::size_t    index)
    : mDataPool(dataPool)
    , mIndex(index)
{ }
        
inline
Macro::Content::const_iterator Macro::Content::begin() const
{
    return (*mDataPool)[mIndex].begin();            
}

inline
Macro::Content::const_iterator Macro::Content::end() const
{
    return (*mDataPool)[mIndex].end();            
}

inline
void Macro::Content::assign(Macro::Content::const_iterator begin,
            Macro::Content::const_iterator end)
{
    mDataPool->insert(mIndex, begin, end);
}

inline
Macro::Content& Macro::Content::operator=(const std::initializer_list<Event>& data)
{
    assign(data.begin(), data.end());

    return *this;
}


inline
Macro::Macro(MacroDataPool* dataPool,
             std::size_t    index)
    : content(dataPool, index)
{ }


#endif
