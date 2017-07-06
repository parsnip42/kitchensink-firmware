#include "storage.h"

namespace
{
constexpr uint8_t SD_CS_PIN = 10;
}

Storage::Storage()
{
    mSdFat.begin(SD_CS_PIN, SPI_HALF_SPEED);
}

Storage::~Storage()
{
}

int Storage::state() const
{
    return mSdFat.card()->errorCode();
}

int Storage::capacityMb() const
{
    return static_cast<int>((0.000512 * mSdFat.card()->cardSize() + 0.5));
}

int Storage::fatType() const
{
    return mSdFat.vol()->fatType();
}

Storage::IStream Storage::read(Region region)
{
    return IStream(mSdFat.open("test.cfg", O_READ));
}

Storage::OStream Storage::write(Region region)
{
    return OStream(mSdFat.open("test.cfg", O_WRITE));
}


Storage::IStream::IStream(File fileHandle)
    : mFileHandle(fileHandle)
{ }

Storage::IStream::~IStream()
{
    mFileHandle.close();
}

Storage::OStream::OStream(File fileHandle)
    : mFileHandle(fileHandle)
{ }

Storage::OStream::~OStream()
{
    mFileHandle.close();
}
        
void Storage::OStream::write(const StrRef& str)
{
    mFileHandle.write(str.begin(), str.size());   
}
