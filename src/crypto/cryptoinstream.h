#ifndef INCLUDED_CRYPTOINSTREAM_H
#define INCLUDED_CRYPTOINSTREAM_H

#include "types/instream.h"
#include "types/strbuf.h"
#include "types/strref.h"

class CryptoInStream : public InStream
{
public:
    enum class Error
    {
        kNone       = 0,
        kCorrupted  = 1,
        kTruncated  = 2,
        kBadHeader  = 3,
        kBadVersion = 4,
    };
    
public:
    CryptoInStream(InStream&     inStream,
                   const StrRef& password);

public:
    virtual ~CryptoInStream() = default;
        
public:
    virtual std::size_t read(OutStream& os, std::size_t len) override;

private:
    void readHeader();
    
private:
    InStream&    mInStream;
    StrRef       mPassword;
    StrBuf<4096> mData;
    Error        mError;
};

#endif
