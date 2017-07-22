#ifndef INCLUDED_MACRO_H
#define INCLUDED_MACRO_H

#include "macrotype.h"
#include "macrodatapool.h"
#include "types/strbuf.h"

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
                std::size_t    index)
            : mDataPool(dataPool)
            , mIndex(index)
        { }
        
    public:
        typedef MacroDataPool::const_iterator const_iterator;

    public:
        const_iterator begin() const
        {
            return (*mDataPool)[mIndex].begin();            
        }

        const_iterator end() const
        {
            return (*mDataPool)[mIndex].end();            
        }
        
        void assign(const_iterator begin,
                    const_iterator end)
        {
            mDataPool->insert(mIndex, begin, end);
        }

        Content& operator=(const std::initializer_list<KeyEvent>& data)
        {
            assign(data.begin(), data.end());

            return *this;
        }
        
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
    MacroType  type;
    StrBuf<24> name;
    StrBuf<24> shortcut;
    Content    content;
};


inline
Macro::Macro(MacroDataPool* dataPool,
             std::size_t    index)
    : content(dataPool, index)
{ }

#endif /* INCLUDED_MACRO_H */
