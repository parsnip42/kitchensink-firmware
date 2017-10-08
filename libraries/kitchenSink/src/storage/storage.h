#ifndef INCLUDED_STORAGE_H
#define INCLUDED_STORAGE_H

#include "types/strbuf.h"
#include "types/strref.h"
#include "types/instream.h"
#include "types/outstream.h"

#include <SdFat.h>

#include <cstdint>

class StrOutStream;

class Storage
{
public:
    class IStream : public InStream
    {
    private:
        explicit IStream(File file);

    public:
        ~IStream();

    public:
        virtual std::size_t read(OutStream& os, std::size_t len) override;

    private:
        File mFileHandle;

    private:
        friend class Storage;
    };

public:
    class OStream : public OutStream
    {
    private:
        explicit OStream(File file);

    public:
        virtual ~OStream();
        
    public:
        virtual void write(const DataRef& data) override;
        void write(char c);

    private:
        File mFileHandle;

    private:
        friend class Storage;
    };

public:
    enum class Region : int
    {
        kConfig          = 0,
        kLayer           = 1,
        kMacro           = 2,
        kSecureMacro     = 3,
        kMultiKey        = 4,
        kSmartKey        = 5,
        kEntropyPoolDump = 6
    };
    
public:
    Storage();

public:
    IStream read(Region region);
    OStream write(Region region);

public:
    int state() const;
    int capacityMb() const;
    int fatType() const;
    
private:
    mutable SdFat mSdFat;
};

#endif

