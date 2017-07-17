#include "types/strref.h"

#include <cctype>

bool StrRef::equalsCase(const StrRef& str) const
{
    if (length() != str.length())
    {
        return false;
    }
    
    for (std::size_t i(0); i < length(); ++i)
    {
        if (std::toupper((*this)[i]) != std::toupper(str[i]))
        {
            return false;
        }
    }
    
    return true;
}

bool StrRef::beginsWith(const StrRef& str) const
{
    return substr(0, str.length()) == str;
}

bool StrRef::endsWith(const StrRef& str) const
{
    return substr(length() - str.length()) == str;
}

bool StrRef::beginsWithCase(const StrRef& str) const
{
    return substr(0, str.length()).equalsCase(str);
}

bool StrRef::endsWithCase(const StrRef& str) const
{
    return substr(length() - str.length()).equalsCase(str);
}

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

