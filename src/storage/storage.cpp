#include "storage.h"

#include "types/strostream.h"

#include <algorithm>

namespace
{
constexpr uint8_t SD_CS_PIN = 10;
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
    return IStream(mSdFat.open("test.cfg", O_READ));
}

Storage::OStream Storage::write(Region region)
{
    mSdFat.remove("test.cfg");
    
    return OStream(mSdFat.open("test.cfg", O_CREAT | O_EXCL | O_WRITE));
}


Storage::IStream::IStream(File fileHandle)
    : mFileHandle(fileHandle)
{ }

Storage::IStream::~IStream()
{
    mFileHandle.close();
}

bool Storage::IStream::readLine(StrOStream& ostream)
{
    char ch;
    
    while (mFileHandle.read(&ch, 1) == 1)
    {
        if (ch == '\n' || ch == '\r')
        {
            return true;
        }
        
        ostream.appendChar(ch);
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
    mFileHandle.write(str.begin(), str.size());   
}
