#include "crypto/cryptoinstream.h"

#include "types/arrayoutstream.h"

namespace
{
constexpr std::size_t kAesBlockSize = 16;

typedef std::array<uint8_t, 32> Value256;
typedef std::array<uint8_t, kAesBlockSize> Value128;
}

CryptoInStream::CryptoInStream(InStream&     inStream,
                                const StrRef& password)
    : mInStream(inStream)
    , mPassword(password)
    , mError(Error::kNone)
{
    readHeader();
}

std::size_t CryptoInStream::read(OutStream& os, std::size_t len)
{
    if (mError != Error::kNone)
    {
        return 0;
    }
    
    return 0;
}

void CryptoInStream::readHeader()
{
    std::array<uint8_t, 128> buffer;
    ArrayOutStream out(buffer);

    // Header
    
    mInStream.read(out, 3);
    if (out.data() != "AES")
    {
        mError = Error::kBadHeader;
        return;
    }

    // File version
    
    out.reset();
    mInStream.read(out, 1);
    if (out.data() != uint8_t('\x02'))
    {
        mError = Error::kBadVersion;
        return;
    }

    // Reserved
    
    out.reset();
    mInStream.read(out, 1);
    if (out.data() != uint8_t('\x00'))
    {
        mError = Error::kCorrupted;
        return;
    }

    // Extension length
    
    out.reset();
    if (mInStream.read(out, 2) != 2)
    {
        mError = Error::kTruncated;
        return;
    }

    std::size_t extLen(std::size_t(out.data()[0]) << 8 | std::size_t(out.data()[1]));

    out.reset();
    if (mInStream.read(out, extLen) != extLen)
    {
        mError = Error::kTruncated;
        return;
    }

    // IV
    
    Value128 iv;
    ArrayOutStream ivOut(iv);
    
    if (mInStream.read(ivOut, iv.size()) != iv.size())
    {
        mError = Error::kTruncated;
        return;
    }

}
