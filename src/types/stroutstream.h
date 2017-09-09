#ifndef INCLUDED_STROUTSTREAM_H
#define INCLUDED_STROUTSTREAM_H

#include "types/strref.h"
#include "types/outstream.h"

#include <cstdint>
#include <cstring>

class StrOutStream : public OutStream
{
public:
    StrOutStream(char*       data,
               std::size_t dataSize);

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


inline
StrOutStream::StrOutStream(char*       data,
                           std::size_t dataSize)
    : mData(data)
    , mDataSize(dataSize)
{ }

inline
StrRef StrOutStream::str() const
{
    return StrRef(mData);
}

#endif

