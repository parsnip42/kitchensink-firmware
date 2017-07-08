#include "storage.h"

#include <algorithm>

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

void Storage::IStream::readToken(char*         data,
                                 std::size_t   len,
                                 const StrRef& separators)
{
    char        ch;
    std::size_t count(0);

    if (len <= 0)
    {
        return;
    }
    
    while (((count + 1) < len) && mFileHandle.read(&ch, 1) == 1)
    {
        if (std::find(separators.begin(), separators.end(), ch) == separators.end())
        {
            data[count++] = ch;
            break;
        }
    }

    while (((count + 1) < len) && mFileHandle.read(&ch, 1) == 1)
    {
        if (std::find(separators.begin(), separators.end(), ch) == separators.end())
        {
            data[count++] = ch;
        }
        else
        {
            break;
        }
    }

    data[count] = '\0';
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
