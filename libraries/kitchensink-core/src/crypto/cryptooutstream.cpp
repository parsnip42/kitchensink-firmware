#include "crypto/cryptooutstream.h"

#include "crypto/entropypool.h"
#include "types/arrayutil.h"
#include "types/stroutstream.h"
#include "config.h"

CryptoOutStream::CryptoOutStream(OutStream&   outStream,
                                const StrRef& password,
                                EntropyPool&  entropyPool)
    : mOutStream(outStream)
    , mPassword(password)
    , mEntropyPool(entropyPool)
    , mData()
    , mDataOut(mData)
{
    // FIXME: Test this in advance - at the moment we're relying on the UI.
    // Note the implicit cast to Key when both types are the same size.
    mEntropyPool.read(mDataKey);

    writeHeader();

    mHMAC.init(mDataKey);
}

CryptoOutStream::~CryptoOutStream()
{
    flush();
}

void CryptoOutStream::writeHeader()
{
    Crypto::SHA256 ivPair;

    mEntropyPool.read(ivPair);

    Crypto::IV iv;

    ArrayUtil<Crypto::SHA256>::split(ivPair, iv, mDataIv);

    auto key(CryptoUtil::stretch(mPassword, iv));
        
    std::array<uint8_t, sizeof(mDataIv) + sizeof(mDataKey)> dataIvKey;

    ArrayUtil<decltype(dataIvKey)>::join(mDataIv, mDataKey, dataIvKey);
    
    std::array<uint8_t, sizeof(mDataIv) + sizeof(mDataKey)> dataIvKeyCrypt;

    CryptoUtil::encrypt(key,
                        iv,
                        dataIvKey,
                        dataIvKeyCrypt);
    
    Crypto::HMAC dataIvKeyHmac(CryptoUtil::hmac(key, dataIvKeyCrypt));

    mOutStream.write("AES");
    mOutStream.write(uint8_t('\x02'));
    mOutStream.write(uint8_t('\x00'));

    StrRef createdBy("CREATED_BY");
    StrRef creator("kitchenSink");

    mOutStream.write(uint8_t('\x00'));
    mOutStream.write(static_cast<char>(createdBy.length() + creator.length() + 1));
    mOutStream.write(createdBy);
    mOutStream.write(uint8_t('\x00'));
    mOutStream.write(creator);

    mOutStream.write(uint8_t('\x00'));
    mOutStream.write(uint8_t('\x00'));
    
    mOutStream.write(iv);
    mOutStream.write(dataIvKeyCrypt);
    mOutStream.write(dataIvKeyHmac);
}

std::size_t CryptoOutStream::write(const DataRef& data)
{
    auto currentData = data;

    while (currentData.size() > 0)
    {
        auto written = mDataOut.write(currentData);
        
        if (mDataOut.remaining() == 0)
        {
            std::array<uint8_t, Crypto::kAesBlockSize> cryptData;
            
            mDataIv = CryptoUtil::encrypt(mDataKey,
                                          mDataIv,
                                          kBufferSize,
                                          mData.begin(),
                                          cryptData.begin());
            
            auto cryptDataRef(DataRef(cryptData.begin(), cryptData.end()));
            
            mHMAC.update(cryptDataRef);
            mOutStream.write(cryptDataRef);

            mDataOut.reset();
        }
        
        currentData = DataRef(currentData.begin() + written, currentData.end());
    }
    
    return data.size();
}

void CryptoOutStream::flush()
{
    auto blockOffset(mDataOut.position() % Crypto::kAesBlockSize);

    if (mDataOut.position() > 0)
    {
        std::array<uint8_t, Crypto::kAesBlockSize> cryptData;
        
        mDataIv = CryptoUtil::encrypt(mDataKey,
                                      mDataIv,
                                      kBufferSize,
                                      mData.begin(),
                                      cryptData.begin());

        auto cryptDataRef(DataRef(cryptData.begin(), cryptData.end()));

        mHMAC.update(cryptDataRef);
        mOutStream.write(cryptDataRef);
        
        mDataOut.reset();
    }
    
    mOutStream.write(uint8_t(blockOffset));

    auto hmac(mHMAC.finish());
    
    mOutStream.write(hmac);
}



















