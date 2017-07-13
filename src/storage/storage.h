#ifndef INCLUDED_STORAGE_H
#define INCLUDED_STORAGE_H

#include "types/strbuf.h"
#include "types/strref.h"

#include <SdFat.h>

#include <cstdint>

class StrOStream;

class Storage
{
public:
    class OStream
    {
    private:
        explicit OStream(File file);

    public:
        ~OStream();
        
    public:
        void write(const StrRef& str);

    private:
        File mFileHandle;

    private:
        friend class Storage;
    };

public:
    class IStream
    {
    private:
        explicit IStream(File file);

    public:
        ~IStream();

    public:
        bool readLine(StrOStream& ostream);
        
    private:
        File mFileHandle;

    private:
        friend class Storage;
    };

public:
    enum class Region : int
    {
        Config = 0
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

#endif /* INCLUDED_STORAGE_H */










