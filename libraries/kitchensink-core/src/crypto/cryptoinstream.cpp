#include "crypto/cryptoinstream.h"

#include "crypto/cryptotypes.h"
#include "crypto/cryptoutil.h"
#include "types/arrayutil.h"
#include "types/arrayoutstream.h"

CryptoInStream::CryptoInStream(InStream&     inStream,
                               const StrRef& password)
    : mInStream(inStream)
    , mPassword(password)
    , mState(State::kReading)
{
    readHeader();
}

std::size_t CryptoInStream::read(OutStream& os, std::size_t len)
{
    if (mState != State::kReading)
    {
        return 0;
    }
    
    do
    {
        mInStream.read(mInBuffer, mInBuffer.remaining());
    }
    while (readBlock() && mState == State::kReading);
    
    return mOutBuffer.read(os, len);
}

void CryptoInStream::readHeader()
{
    std::array<uint8_t, 128> buffer;
    ArrayOutStream out(buffer);

    // Header
    
    mInStream.read(out, 3);
    if (out.data() != "AES")
    {
        mState = State::kBadHeader;
        return;
    }
    
    // File version
    
    out.reset();
    mInStream.read(out, 1);
    if (out.data() != uint8_t('\x02'))
    {
        mState = State::kBadVersion;
        return;
    }

    // Reserved
    
    out.reset();
    mInStream.read(out, 1);
    if (out.data() != uint8_t('\x00'))
    {
        mState = State::kCorrupted;
        return;
    }

    // Skip Extensions

    std::size_t extLen(0);
    
    do
    {
        out.reset();
        if (mInStream.read(out, 2) != 2)
        {
            mState = State::kTruncated;
            return;
        }

        extLen = (std::size_t(out.data()[0]) << 8 |
                  std::size_t(out.data()[1]));

        out.reset();
        if (mInStream.read(out, extLen) != extLen)
        {
            mState = State::kTruncated;
            return;
        }
    } while (extLen != 0);
    
    // IV
    
    Crypto::IV iv;
    
    {
        ArrayOutStream out(iv);
    
        if (mInStream.read(out, iv.size()) != iv.size())
        {
            mState = State::kTruncated;
            return;
        }
    }

    // Encrypted IV + Key
    
    std::array<uint8_t, Crypto::kAesBlockSize + Crypto::kAesKeyLen> dataIvKeyCrypt;

    {
        ArrayOutStream out(dataIvKeyCrypt);
        
        if (mInStream.read(out, dataIvKeyCrypt.size()) != dataIvKeyCrypt.size())
        {
            mState = State::kTruncated;
            return;
        }
    }

    // IV + Key HMAC
    
    Crypto::HMAC dataIvKeyHmac;

    {
        ArrayOutStream out(dataIvKeyHmac);
        
        if (mInStream.read(out, dataIvKeyHmac.size()) != dataIvKeyHmac.size())
        {
            mState = State::kTruncated;
            return;
        }
    }

    // Verify HMAC
    
    auto key(CryptoUtil::stretch(mPassword, iv));
    
    if (dataIvKeyHmac != CryptoUtil::hmac(key, dataIvKeyCrypt))
    {
        mState = State::kBadHmac;
        return;
    }
    
    std::array<uint8_t, Crypto::kAesBlockSize + Crypto::kAesKeyLen> dataIvKey;

    CryptoUtil::decrypt(key,
                        iv,
                        dataIvKeyCrypt,
                        dataIvKey);
    
    ArrayUtil<decltype(dataIvKey)>::split(dataIvKey, mDataIv, mDataKey);

    mHMAC.init(mDataKey);
}

bool CryptoInStream::readBlock()
{
    static constexpr size_t SuffixLen = 33;
    
    if (mInBuffer.size() < Crypto::kAesBlockSize)
    {
        return false;
    }

    if (mOutBuffer.remaining() < Crypto::kAesBlockSize)
    {
        return false;
    }
    
    std::array<uint8_t, Crypto::kAesBlockSize> inBlock;
    std::array<uint8_t, Crypto::kAesBlockSize> outBlock;
    ArrayOutStream inBlockStream(inBlock);
    
    mInBuffer.read(inBlockStream, Crypto::kAesBlockSize);
    mHMAC.update(DataRef(inBlock.begin(), inBlock.end()));
    
    mDataIv = CryptoUtil::decrypt(mDataKey,
                                  mDataIv,
                                  Crypto::kAesBlockSize,
                                  inBlock.begin(),
                                  outBlock.begin());
    
    auto blockSize(Crypto::kAesBlockSize);

    if (mInBuffer.size() == SuffixLen)
    {
        std::array<uint8_t, SuffixLen> suffix;
        ArrayOutStream suffixStream(suffix);
        
        mInBuffer.read(suffixStream, suffix.size());
        
        auto cipherTextTrailing(Crypto::kAesBlockSize - suffix[0]);
        
        blockSize = Crypto::kAesBlockSize - (cipherTextTrailing % Crypto::kAesBlockSize);
            
        Crypto::HMAC dataHmac;
            
        std::copy(suffix.begin() + 1,
                  suffix.begin() + SuffixLen,
                  dataHmac.begin());

        auto expectedHmac(mHMAC.finish());

        if (dataHmac != expectedHmac)
        {
            mState = State::kBadDataHmac;
        }
        else
        {
            mState = State::kValidated;
        }
    }
    
    auto blockData(DataRef(outBlock.begin(), outBlock.begin() + blockSize));
    
    mOutBuffer.write(blockData);

    return true;
}
