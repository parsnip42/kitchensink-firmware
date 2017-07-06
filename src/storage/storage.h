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
        void readLine(StrBuf<N>& str);

    private:
        File mFileHandle;

    private:
        friend class Storage;
    };

public:
    enum class Region : int
    {
        kConfig = 0
    };
    
public:
    Storage();
    ~Storage();

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
inline
void Storage::IStream::readLine(StrBuf<N>& str)
{
    mFileHandle.fgets(str.data(), N);   
}

#endif /* INCLUDED_STORAGE_H */










