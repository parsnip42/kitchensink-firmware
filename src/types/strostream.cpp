#include "types/strostream.h"

#include "types/strref.h"

#include <cstdio>
#include <cstring>
#include <string.h>

void StrOStream::reset() const
{
    mData[0] = '\0';
}

const StrOStream& StrOStream::appendStr(const StrRef& str) const
{
    auto currentLength(strlen(mData));

    strlcpy(mData + currentLength,
            str.begin(),
            std::min(str.length() + 1, mDataSize - currentLength));
    
    return *this;
}

const StrOStream& StrOStream::appendChar(char c) const
{
    auto currentLength(strlen(mData));

    if (currentLength < mDataSize - 1)
    {
        mData[currentLength] = c;
        mData[currentLength + 1] = '\0';
    }

    return *this;    
}

const StrOStream& StrOStream::appendInt(int n, const char* fmt) const
{
    auto currentLength(strlen(mData));

    snprintf(mData + currentLength, mDataSize - currentLength, fmt, n);

    return *this;
}
