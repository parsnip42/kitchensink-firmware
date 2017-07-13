#include "types/strref.h"

StrRef StrRef::trim() const
{
    const_iterator trimBegin(begin());

    while (trimBegin != end() &&
           (*trimBegin == ' ' || *trimBegin == '\t'));
    {
        ++trimBegin;
    }

    const_iterator trimEnd(end());
    
    while (trimEnd != trimBegin)
    {
        --trimEnd;

        if (!(*trimEnd == ' ' || *trimBegin == '\t'))
        {
            ++trimEnd;
            break;
        }
    }
    
    return StrRef(trimBegin, trimEnd);
}

