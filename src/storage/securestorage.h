#ifndef INCLUDED_SECURESTORAGE_H
#define INCLUDED_SECURESTORAGE_H

#include "storage/storage.h"
#include "types/outstream.h"
#include "types/strbuf.h"
#include "types/stroutstream.h"
#include "types/arrayoutstream.h"

class DataRef;
class EntropyPool;

class SecureStorage
{
public:
    class IStream : public InStream
    {
    private:
        IStream(Storage::IStream istream,
                const StrRef&    password);

    public:
        virtual ~IStream() = default;
        
    public:
        virtual std::size_t read(OutStream& os, std::size_t len) override;

    private:
        Storage::IStream mIStream;
        StrRef           mPassword;
        StrBuf<4096>     mData;

    private:
        friend class SecureStorage;
    };

public:
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

public:
    explicit SecureStorage(Storage& storage);

public:
    IStream read(const StrRef&   password,
                 Storage::Region region);

private:
    Storage& mStorage;
};

#endif


