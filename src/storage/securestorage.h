#ifndef INCLUDED_SECURESTORAGE_H
#define INCLUDED_SECURESTORAGE_H

#include "storage/storage.h"
#include "types/outstream.h"
#include "types/strbuf.h"
#include "types/stroutstream.h"
#include "types/arrayoutstream.h"

class DataRef;
class EntropyPool;

namespace SecureStorage
{

class IStream : public InStream
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
    IStream(InStream&     inStream,
            const StrRef& password);

public:
    virtual ~IStream() = default;
        
public:
    virtual std::size_t read(OutStream& os, std::size_t len) override;

private:
    void readHeader();
    
private:
    InStream&    mInStream;
    StrRef       mPassword;
    StrBuf<4096> mData;
    Error        mError;

private:
    friend class SecureStorage;
};

class OStream : public OutStream
{
public:
    OStream(OutStream&    ostream,
            const StrRef& password,
            EntropyPool&  entropyPool);

public:
    virtual ~OStream();
        
public:
    virtual void write(const DataRef& data) override;
        
private:
    OutStream&                mOStream;
    StrRef                    mPassword;
    EntropyPool&              mEntropyPool;
    std::array<uint8_t, 4096> mData;
    ArrayOutStream            mDataOut;
        
private:
    friend class SecureStorage;
};

};

#endif


