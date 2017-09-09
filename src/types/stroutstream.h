#ifndef INCLUDED_STROUTSTREAM_H
#define INCLUDED_STROUTSTREAM_H

#include "types/strref.h"
#include "types/strbuf.h"
#include "types/stroutstream.h"
#include "types/outstream.h"

#include <cstdint>
#include <cstring>

class StrOutStream : public OutStream
{
public:
    template <std::size_t Capacity>
    StrOutStream(StrBuf<Capacity>& buf);

public:
    virtual void write(const StrRef& str) override;

public:
    StrRef str() const;
    void reset() const;

public:
    const StrOutStream& appendStr(const StrRef& str) const;
    const StrOutStream& appendChar(char c) const;
    const StrOutStream& appendInt(int n, const char* fmt = "%d") const;
    
private:
    char*       mData;
    std::size_t mDataSize;
};


template <std::size_t Capacity>
inline
StrOutStream::StrOutStream(StrBuf<Capacity>& buf)
    : mData(buf.begin())
    , mDataSize(buf.capacity() + 1) // StrBuf is null-terminated
{ }

inline
StrRef StrOutStream::str() const
{
    return StrRef(mData);
}

#endif




