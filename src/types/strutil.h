#ifndef INCLUDED_STRUTIL_H
#define INCLUDED_STRUTIL_H

#include "types/strref.h"

namespace StrUtil
{

bool parseUInt(const StrRef& input,
               int&          output);

StrRef nextToken(const StrRef& input,
                 const StrRef& delim,
                 const StrRef& last = StrRef());

};

#endif /* INCLUDED_STRUTIL_H */
