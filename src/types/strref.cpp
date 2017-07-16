#include "types/strref.h"

StrRef StrRef::trim() const
{
    const_iterator trimBegin(begin());

    while (trimBegin != end() &&
           (*trimBegin == ' ' || *trimBegin == '\t'))
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

bool StrRef::beginsWith(const StrRef& str) const
{
    return substr(0, str.length()) == str;
}

bool StrRef::endsWith(const StrRef& str) const
{
    return substr(length() - str.length()) == str;
}
