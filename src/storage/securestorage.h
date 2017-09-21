#ifndef INCLUDED_SECURESTORAGE_H
#define INCLUDED_SECURESTORAGE_H

#include "storage/storage.h"
#include "types/outstream.h"
#include "types/strbuf.h"
#include "types/stroutstream.h"

class EntropyPool;

class SecureStorage
{
public:
    class OStream : public OutStream
    {
    private:
        explicit OStream(Storage::OStream ostream,
                         const StrRef&    password,
                         EntropyPool&     entropyPool);

    public:
        virtual ~OStream();
        
    public:
        virtual void write(const StrRef& str) override;

    private:
        Storage::OStream mOStream;
        const StrRef&    mPassword;
        EntropyPool&     mEntropyPool;
        StrBuf<4096>     mData;
        StrOutStream     mDataOut;
        
    private:
        friend class SecureStorage;
    };

public:
    explicit SecureStorage(Storage& storage);

public:
    // IStream read(Storage::Region region);
    OStream write(const StrRef&   password,
                  EntropyPool&    entropyPool,
                  Storage::Region region);

private:
    Storage& mStorage;
};

#endif


