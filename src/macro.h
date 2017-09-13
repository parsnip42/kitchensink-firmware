#ifndef INCLUDED_MACRO_H
#define INCLUDED_MACRO_H

#include "macrodatapool.h"
#include "types/strbuf.h"
#include "config.h"

class Macro
{
public:
    enum class Type : uint8_t
    {
        kSync     = 0,
        kRealtime = 1,
        kInvert   = 2
    };

public:
    class Content
    {
    public:
        typedef ArrayPool<Event>::const_iterator const_iterator;

    private:
        Content() = default;
        Content(ArrayPool<Event>* eventPool,
                std::size_t       index);
        
    public:
        const_iterator begin() const;
        const_iterator end() const;
        
        void assign(const_iterator begin,
                    const_iterator end);
        
    private:
        ArrayPool<Event>* mEventPool;
        std::size_t       mIndex;

    private:
        friend class Macro;
    };
    
public:
    Macro() = default;
    Macro(ArrayPool<Event>* eventPool,
          std::size_t       index);

public:
    Type                              type;
    StrBuf<Config::kMacroNameLen>     name;
    StrBuf<Config::kMacroShortcutLen> shortcut;
    Content                           content;
};


inline
Macro::Content::Content(ArrayPool<Event>* eventPool,
                        std::size_t       index)
    : mEventPool(eventPool)
    , mIndex(index)
{ }
        
inline
Macro::Content::const_iterator Macro::Content::begin() const
{
    return (*mEventPool)[mIndex].begin();            
}

inline
Macro::Content::const_iterator Macro::Content::end() const
{
    return (*mEventPool)[mIndex].end();            
}

inline
void Macro::Content::assign(Macro::Content::const_iterator begin,
                            Macro::Content::const_iterator end)
{
    mEventPool->insert(mIndex, begin, end);
}

inline
Macro::Macro(ArrayPool<Event>* dataPool,
             std::size_t       index)
    : type(Type::kSync)
    , content(dataPool, index)
{ }


#endif
