#include "crypto/cryptooutstream.h"

#include "crypto/cryptotypes.h"
#include "crypto/cryptoutil.h"
#include "crypto/entropypool.h"
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
{ }

CryptoOutStream::~CryptoOutStream()
{
    auto iv(mEntropyPool.read128());

    auto key(CryptoUtil::stretch(mPassword, iv));
    
    auto dataIv(mEntropyPool.read128());

    auto dataKey(mEntropyPool.read());

    std::array<uint8_t, dataIv.size() + dataKey.size()> dataIvKey;

    std::copy(dataIv.begin(), dataIv.end(), dataIvKey.begin());
    std::copy(dataKey.begin(), dataKey.end(), dataIvKey.begin() + dataIv.size());
    
    std::array<uint8_t, dataIv.size() + dataKey.size()> dataIvKeyCrypt;

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

    auto blockCount((mDataOut.position() + Crypto::kAesBlockSize - 1) / Crypto::kAesBlockSize);
    auto blockOffset(mDataOut.position() % Crypto::kAesBlockSize);
    auto cryptSize(blockCount * Crypto::kAesBlockSize);
    
    std::array<uint8_t, 4096> cryptData;
    
    CryptoUtil::encrypt(dataKey,
                        dataIv,
                        cryptSize,
                        mData.begin(),
                        cryptData.begin());

    Crypto::HMAC cryptDataHmac(CryptoUtil::hmac(dataKey,
                                                cryptData.begin(),
                                                cryptData.begin() + cryptSize));

    mOutStream.write(DataRef(cryptData.begin(),
                             cryptData.begin() + cryptSize));
    mOutStream.write(uint8_t(blockOffset));
    mOutStream.write(cryptDataHmac);
}

void CryptoOutStream::write(const DataRef& data)
{
    mDataOut.write(data);
}
