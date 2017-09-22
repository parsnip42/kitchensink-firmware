#include "crypto/cryptoinstream.h"

#include "crypto/cryptotypes.h"
#include "crypto/cryptoutil.h"

#include "types/arrayoutstream.h"

CryptoInStream::CryptoInStream(InStream&     inStream,
                               const StrRef& password)
    : mInStream(inStream)
    , mPassword(password)
    , mDataStream(DataRef())
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
    
    return mDataStream.read(os, len);
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
    
    Crypto::IV  dataIv;
    Crypto::Key dataKey;

    std::copy(dataIvKey.begin(),
              dataIvKey.begin() + dataIv.size(),
              dataIv.begin());

    std::copy(dataIvKey.begin() + dataIv.size(),
              dataIvKey.begin() + dataIv.size() + dataKey.size(),
              dataKey.begin());
    
    ArrayOutStream ctOut(mContent);

    auto contentLen(mInStream.read(ctOut, mContent.size()));

    if (contentLen <= 33)
    {
        mError = Error::kTruncated;
        return;
    }
    
    auto cipherTextLen = contentLen - 33;

    if ((cipherTextLen % Crypto::kAesBlockSize) != 0)
    {
        mError = Error::KBadAlignment;
        return;
    }

    Crypto::HMAC dataHmac;

    std::copy(mContent.begin() + contentLen - 32,
              mContent.begin() + contentLen,
              dataHmac.begin());

    if (dataHmac != CryptoUtil::hmac(dataKey,
                                     mContent.begin(),
                                     mContent.begin() + cipherTextLen))
    {
        mError = Error::kBadDataHmac;
        return;
    }

    CryptoUtil::decrypt(dataKey,
                        dataIv,
                        cipherTextLen,
                        mContent.begin(),
                        mData.begin());

    std::size_t cipherTextTrailing(Crypto::kAesBlockSize - *(mContent.begin() + contentLen - 33));

    cipherTextLen -= cipherTextTrailing % Crypto::kAesBlockSize;
    
    mDataStream = DataRefInStream(DataRef(mData.begin(), mData.begin() + cipherTextLen));
    mError = Error::kNone;
}



















