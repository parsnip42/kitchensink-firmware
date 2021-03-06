#include "storage/storage.h"

#include "types/stroutstream.h"

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
    case Storage::Region::kConfig:
        return "config.ini";

    case Storage::Region::kLayer:
        return "layer.ini";
        
    case Storage::Region::kMacro:
        return "macro.ini";

    case Storage::Region::kSecureMacro:
        return "securemacro.ini.aes";

    case Storage::Region::kMultiKey:
        return "multi.ini";

    case Storage::Region::kSmartKey:
        return "smart.ini";

    case Storage::Region::kEntropyPoolDump:
        return "entropy.dat";

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

std::size_t Storage::IStream::read(OutStream& os, std::size_t len)
{
    std::size_t count(0);
    uint8_t ch;

    while (count < len && mFileHandle.read(&ch, 1) == 1)
    {
        os.write(ch);
        ++count;
    }

    return count;
}

Storage::OStream::OStream(File fileHandle)
    : mFileHandle(fileHandle)
{ }

Storage::OStream::~OStream()
{
    mFileHandle.close();
}
        
std::size_t Storage::OStream::write(const DataRef& data)
{
    mFileHandle.write(data.begin(), data.size());

    return data.size();
}

void Storage::OStream::write(char c)
{
    mFileHandle.write(c);   
}
