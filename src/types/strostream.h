#ifndef INCLUDED_STROSTREAM_H
#define INCLUDED_STROSTREAM_H

#include "types/strbuf.h"

#include <cstdint>
#include <cstring>

class StrRef;

class StrOStream
{
public:
    template <std::size_t N>
    StrOStream(StrBuf<N>& strBuf);

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


template <std::size_t N>
inline
StrOStream::StrOStream(StrBuf<N>& strBuf)
    : mData(strBuf.begin())
    , mDataSize(strBuf.capacity() + 1)
{ }

inline
StrRef StrOStream::str() const
{
    return StrRef(mData);
}

#endif /* INCLUDED_STROSTREAM_H */










