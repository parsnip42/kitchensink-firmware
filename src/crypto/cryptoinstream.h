#ifndef INCLUDED_CRYPTOINSTREAM_H
#define INCLUDED_CRYPTOINSTREAM_H

#include "types/instream.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "crypto/cryptotypes.h"

class CryptoInStream : public InStream
{
public:
    enum class Error
    {
        kNone         = 0,
        kCorrupted    = 1,
        kTruncated    = 2,
        kBadHeader    = 3,
        kBadVersion   = 4,
        kBadHmac      = 5,
        kBadDataHmac  = 6,
        KBadAlignment = 7
    };
    
public:
    CryptoInStream(InStream&     inStream,
                   const StrRef& password);

public:
    virtual ~CryptoInStream() = default;
        
public:
    virtual std::size_t read(OutStream& os, std::size_t len) override;

    Error error() const;
    
private:
    void readHeader();
    
private:
    InStream&                 mInStream;
    StrRef                    mPassword;
    std::array<uint8_t, 4096> mContent;
    std::array<uint8_t, 4096> mData;
    Error                     mError;
};


inline
CryptoInStream::Error CryptoInStream::error() const
{
    return mError;
}

#endif
