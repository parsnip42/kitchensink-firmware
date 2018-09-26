#ifndef INCLUDED_CRYPTOINSTREAM_H
#define INCLUDED_CRYPTOINSTREAM_H

#include "crypto/cryptotypes.h"
#include "types/datarefinstream.h"
#include "types/instream.h"
#include "types/strbuf.h"
#include "types/strref.h"

class CryptoInStream : public InStream
{
public:
    enum class Error
    {
        kUninitialized = -1,
        kNone          = 0,
        kCorrupted     = 1,
        kTruncated     = 2,
        kBadHeader     = 3,
        kBadVersion    = 4,
        kBadHmac       = 5,
        kBadDataHmac   = 6,
        KBadAlignment  = 7
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
    Crypto::Key               mDataKey;
    Crypto::IV                mDataIv;

    // FIXME
    std::size_t               mPosition;
    std::array<uint8_t, 8192> mContent;
    std::size_t               mCipherTextLen;

    Error                     mError;
};


inline
CryptoInStream::Error CryptoInStream::error() const
{
    return mError;
}

#endif
