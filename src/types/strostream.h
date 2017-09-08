#ifndef INCLUDED_STROSTREAM_H
#define INCLUDED_STROSTREAM_H

#include "types/strref.h"

#include <cstdint>
#include <cstring>

class StrOStream
{
public:
    StrOStream(char*       data,
               std::size_t dataSize);

public:
    StrRef str() const;
    void reset() const;

public:
    const StrOStream& appendStr(const StrRef& str) const;
    const StrOStream& appendChar(char c) const;
    const StrOStream& appendInt(int n, const char* fmt = "%d") const;
    
private:
    char*       mData;
    std::size_t mDataSize;
};


inline
StrOStream::StrOStream(char*       data,
                       std::size_t dataSize)
    : mData(data)
    , mDataSize(dataSize)
{ }

inline
StrRef StrOStream::str() const
{
    return StrRef(mData);
}

#endif

