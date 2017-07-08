#ifndef INCLUDED_STROSTREAM_H
#define INCLUDED_STROSTREAM_H

#include "types/strbuf.h"

#include <cstdint>

class StrRef;

class StrOStream
{
public:
    template <std::size_t N>
    explicit StrOStream(StrBuf<N>& strBuf);

public:
    std::size_t length() const;
    std::size_t capacity() const;

    StrOStream& appendStr(const StrRef& str);
    StrOStream& appendChar(char c);
    StrOStream& appendInt(int n, const char* fmt = "%d");
    
private:
    char*       mData;
    std::size_t mCapacity;
};


template <std::size_t N>
inline
StrOStream::StrOStream(StrBuf<N>& strBuf)
    : mData(strBuf.data())
    , mCapacity(strBuf.capacity())
{ }

#endif /* INCLUDED_STROSTREAM_H */










