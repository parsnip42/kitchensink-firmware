#ifndef INCLUDED_STORAGE_H
#define INCLUDED_STORAGE_H

#include "types/strbuf.h"
#include "types/strref.h"

#include <SdFat.h>

#include <cstdint>

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
        template <std::size_t N>
        void readToken(StrBuf<N>& str, const StrRef& separators);

    private:
        void readToken(char*         data,
                       std::size_t   len,
                       const StrRef& separators);
        
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


template <std::size_t N>
void Storage::IStream::readToken(StrBuf<N>& str, const StrRef& separators)
{
    Storage::IStream::readToken(str.data(), N, separators);
}

#endif /* INCLUDED_STORAGE_H */










