#include "crypto/cryptoinstream.h"

#include "crypto/cryptotypes.h"
#include "crypto/cryptoutil.h"
#include "types/arrayutil.h"
#include "types/arrayoutstream.h"

CryptoInStream::CryptoInStream(InStream&     inStream,
                               const StrRef& password)
    : mInStream(inStream)
    , mPassword(password)
    , mError(Error::kUninitialized)
{
    readHeader();
}

std::size_t CryptoInStream::read(OutStream& os, std::size_t len)
{
    if (mError != Error::kNone)
    {
        return 0;
    }

    std::size_t read(0);

    while (true)
    {
        mInStream.read(mStream, mStream.remaining());
        
        if (mStream.size() > (33 + Crypto::kAesBlockSize))
        {
            std::array<uint8_t, Crypto::kAesBlockSize> inBlock;
            std::array<uint8_t, Crypto::kAesBlockSize> outBlock;
            ArrayOutStream inBlockStream(inBlock);

            mStream.read(inBlockStream, Crypto::kAesBlockSize);
            mHMAC.update(DataRef(inBlock.begin(), inBlock.end()));
        
            mDataIv = CryptoUtil::decrypt(mDataKey,
                                          mDataIv,
                                          Crypto::kAesBlockSize,
                                          inBlock.begin(),
                                          outBlock.begin());

            auto blockData(DataRef(outBlock.begin(), outBlock.end()));
            
            os.write(blockData);
            
            read += Crypto::kAesBlockSize;
        }
        else if (mStream.size() == (33 + Crypto::kAesBlockSize))
        {
            std::array<uint8_t, Crypto::kAesBlockSize> inBlock;
            std::array<uint8_t, Crypto::kAesBlockSize> outBlock;
            ArrayOutStream inBlockStream(inBlock);

            mStream.read(inBlockStream, Crypto::kAesBlockSize);
            mHMAC.update(DataRef(inBlock.begin(), inBlock.end()));

            mDataIv = CryptoUtil::decrypt(mDataKey,
                                          mDataIv,
                                          Crypto::kAesBlockSize,
                                          inBlock.begin(),
                                          outBlock.begin());

            ////////////////////////////////////////
        
            std::array<uint8_t, 33> suffix;
            ArrayOutStream suffixStream(suffix);

            mStream.read(suffixStream, suffix.size());

            auto cipherTextTrailing(Crypto::kAesBlockSize - suffix[0]);
            auto subBlockSize(Crypto::kAesBlockSize - (cipherTextTrailing % Crypto::kAesBlockSize));

            os.write(DataRef(outBlock.begin(), outBlock.begin() + subBlockSize));
            
            read += subBlockSize;
        
            Crypto::HMAC dataHmac;
            
            std::copy(suffix.begin() + 1,
                      suffix.begin() + 33,
                      dataHmac.begin());

            auto expectedHmac(mHMAC.finish());

            if (dataHmac != expectedHmac)
            {
                mError = Error::kBadHmac;
            }
            
            break;
        }
        else if (mStream.size() == 0)
        {
            break;
        }
        else
        {
            mError = Error::kTruncated;
            break;
        }
    }

    return read;
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

    // Skip Extensions

    std::size_t extLen(0);
    
    do
    {
        out.reset();
        if (mInStream.read(out, 2) != 2)
        {
            mError = Error::kTruncated;
            return;
        }

        extLen = (std::size_t(out.data()[0]) << 8 |
                  std::size_t(out.data()[1]));

        out.reset();
        if (mInStream.read(out, extLen) != extLen)
        {
            mError = Error::kTruncated;
            return;
        }
    } while (extLen != 0);
    
    // IV
    
    Crypto::IV iv;
    
    {
        ArrayOutStream out(iv);
    
        if (mInStream.read(out, iv.size()) != iv.size())
        {
            mError = Error::kTruncated;
            return;
        }
    }

    // Encrypted IV + Key
    
    std::array<uint8_t, Crypto::kAesBlockSize + Crypto::kAesKeyLen> dataIvKeyCrypt;

    {
        ArrayOutStream out(dataIvKeyCrypt);
        
        if (mInStream.read(out, dataIvKeyCrypt.size()) != dataIvKeyCrypt.size())
        {
            mError = Error::kTruncated;
            return;
        }
    }

    // IV + Key HMAC
    
    Crypto::HMAC dataIvKeyHmac;

    {
        ArrayOutStream out(dataIvKeyHmac);
        
        if (mInStream.read(out, dataIvKeyHmac.size()) != dataIvKeyHmac.size())
        {
            mError = Error::kTruncated;
            return;
        }
    }

    // Verify HMAC
    
    auto key(CryptoUtil::stretch(mPassword, iv));
    
    if (dataIvKeyHmac != CryptoUtil::hmac(key, dataIvKeyCrypt))
    {
        mError = Error::kBadHmac;
        return;
    }
    
    std::array<uint8_t, Crypto::kAesBlockSize + Crypto::kAesKeyLen> dataIvKey;

    CryptoUtil::decrypt(key,
                        iv,
                        dataIvKeyCrypt,
                        dataIvKey);
    
    ArrayUtil<decltype(dataIvKey)>::split(dataIvKey, mDataIv, mDataKey);

    mHMAC.init(mDataKey);
    
    mError = Error::kNone;
}

