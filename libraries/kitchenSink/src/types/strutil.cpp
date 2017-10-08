#include "types/strutil.h"

#include "types/range.h"

#include <algorithm>

namespace StrUtil
{

namespace
{

// Regular std::pow() seems to be pulling in an extra 5KB.
int smPow(int n, int p)
{
    int value(1);
    
    while (p--)
    {
        value *= n;
    }

    return value;
}

}

bool parseUInt(const StrRef& input,
               int&          output)
{
    if (input.empty())
    {
        return false;
    }
    
    Range<StrRef::const_iterator> range(input.begin(), input.end());
    int p(0);
    
    output = 0;
    
    for (auto c : range.reverse())
    {
        if (c >= '0' && c <= '9')
        {
            output += static_cast<int>(c - '0') * smPow(10, p++);
        }
        else
        {
            return false;
        }
    }

    return true;
}

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

bool cut(const StrRef& input,
         StrRef&       tokenA,
         char          separator,
         StrRef&       tokenB)
{
    auto centre(std::find(input.begin(), input.end(), separator));

    if (centre != input.end())
    {
        tokenA = StrRef(input.begin(), centre);
        tokenB = StrRef(centre + 1, input.end());

        return true;
    }

    return false;
}

bool cutTrim(const StrRef& input,
             StrRef&       tokenA,
             char          separator,
             StrRef&       tokenB)
{
    if (cut(input.trim(),
            tokenA,
            separator,
            tokenB))
    {
        tokenA = tokenA.trim();
        tokenB = tokenB.trim();
        
        return true;
    }
    
    return false;
}

};
