#include "types/strostream.h"

#include "types/strref.h"

#include <string.h>

std::size_t StrOStream::length() const
{
    return strlen(mData);
}

std::size_t StrOStream::capacity() const
{
    return mCapacity;
}

StrOStream& StrOStream::appendStr(const StrRef& str)
{
    auto currentLength(length());

    strlcpy(mData + currentLength,
            str.begin(),
            std::min(str.size() + 1, capacity() - currentLength));
    
    return *this;
}

StrOStream& StrOStream::appendChar(char c)
{
    auto currentLength(length());

    if (currentLength < capacity() - 1)
    {
        mData[currentLength] = c;
        mData[currentLength + 1] = '\0';
    }

    return *this;    
}

StrOStream& StrOStream::appendInt(int n, const char* fmt)
{
    auto currentLength(length());

    snprintf(mData + currentLength, capacity() - currentLength, fmt, n);

    return *this;
}
