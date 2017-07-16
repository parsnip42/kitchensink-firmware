#include "storage.h"

#include "types/strostream.h"

#include <algorithm>

namespace
{
constexpr uint8_t SD_CS_PIN = 10;
}

namespace
{
const char* getRegionFile(Storage::Region region)
{
    switch (region)
    {
    case Storage::Region::Config:
        return "config.ini";

    case Storage::Region::Layer:
        return "layer.ini";
        
    case Storage::Region::Macro:
        return "macro.ini";

    default:
        return "unknown.ini";
    }
}
}

Storage::Storage()
{
    mSdFat.begin(SD_CS_PIN, SPI_HALF_SPEED);
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
    return IStream(mSdFat.open(getRegionFile(region), O_READ));
}

Storage::OStream Storage::write(Region region)
{
    auto regionFile(getRegionFile(region));
    
    mSdFat.remove(regionFile);
    
    return OStream(mSdFat.open(regionFile, O_CREAT | O_EXCL | O_WRITE));
}


Storage::IStream::IStream(File fileHandle)
    : mFileHandle(fileHandle)
{ }

Storage::IStream::~IStream()
{
    mFileHandle.close();
}

bool Storage::IStream::readLine(const StrOStream& os)
{
    char ch;

    os.reset();
    
    while (mFileHandle.read(&ch, 1) == 1)
    {
        if (ch == '\n' || ch == '\r')
        {
            return true;
        }
        
        os.appendChar(ch);
    }

    return false;
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
    mFileHandle.write(str.begin(), str.length());   
}
