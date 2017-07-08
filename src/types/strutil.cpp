#include "strutil.h"

#include <algorithm>

namespace StrUtil
{

StrRef nextToken(const StrRef& input,
                 const StrRef& delim,
                 const StrRef& last)
{
    auto tokenBegin(!last.empty() ? last.end() : input.begin());

    while ((tokenBegin != input.end()) &&
           std::find(delim.begin(), delim.end(), *tokenBegin) != delim.end())
    {
        ++tokenBegin;
    }

    auto tokenEnd(tokenBegin);
    
    while ((tokenEnd != input.end()) &&
           (std::find(delim.begin(), delim.end(), *tokenEnd) == delim.end()))
    {
        ++tokenEnd;
    }

    return StrRef(tokenBegin, tokenEnd);
}

};
