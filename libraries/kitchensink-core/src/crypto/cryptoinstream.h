#ifndef INCLUDED_CRYPTOINSTREAM_H
#define INCLUDED_CRYPTOINSTREAM_H

#include "crypto/cryptotypes.h"
#include "crypto/cryptoutil.h"
#include "crypto/hmaccontext.h"
#include "types/datarefinstream.h"
#include "types/circularstream.h"
#include "types/instream.h"
#include "types/strbuf.h"
#include "types/strref.h"

class CryptoInStream : public InStream
{
public:
    enum class State
    {
        kReading       = 0,
        kCorrupted     = 1,
        kTruncated     = 2,
        kBadHeader     = 3,
        kBadVersion    = 4,
        kBadHmac       = 5,
        kBadDataHmac   = 6,

        // Content should be considered untrusted or corrupted until state is
        // marked with this.
        kValidated     = 10
    };
    
public:
    CryptoInStream(InStream&     inStream,
                   const StrRef& password);

public:
    virtual ~CryptoInStream() = default;
        
public:
    virtual std::size_t read(OutStream& os, std::size_t len) override;

    State state() const;
    
private:
    void readHeader();
    bool readBlock();

private:
    InStream&                                 mInStream;
    StrRef                                    mPassword;
    Crypto::Key                               mDataKey;
    Crypto::IV                                mDataIv;
    HMACContext                               mHMAC;
    CircularStream<Crypto::kAesBlockSize * 8> mInBuffer;
    CircularStream<Crypto::kAesBlockSize * 8> mOutBuffer;
    State                                     mState;
};


inline
CryptoInStream::State CryptoInStream::state() const
{
    return mState;
}

#endif



