#ifndef INCLUDED_CRYPTOOUTSTREAM_H
#define INCLUDED_CRYPTOOUTSTREAM_H

#include "types/outstream.h"
#include "types/strbuf.h"
#include "types/stroutstream.h"
#include "types/arrayoutstream.h"

class DataRef;
class EntropyPool;

class CryptoOutStream : public OutStream
{
public:
    CryptoOutStream(OutStream&    outStream,
                    const StrRef& password,
                    EntropyPool&  entropyPool);

public:
    virtual ~CryptoOutStream();
        
public:
    virtual void write(const DataRef& data) override;
        
private:
    OutStream&                mOutStream;
    StrRef                    mPassword;
    EntropyPool&              mEntropyPool;
    std::array<uint8_t, 4096> mData;
    ArrayOutStream            mDataOut;
        
private:
    friend class SecureStorage;
};

#endif
