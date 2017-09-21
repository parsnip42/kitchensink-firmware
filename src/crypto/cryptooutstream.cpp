#include "crypto/cryptooutstream.h"

#include "crypto/entropypool.h"
#include "types/stroutstream.h"
#include "config.h"

#include <mbedtls/aes.h>
#include <mbedtls/sha256.h>
#include <mbedtls/md.h>

namespace
{
constexpr std::size_t kAesBlockSize = 16;

typedef std::array<uint8_t, 32> Value256;
typedef std::array<uint8_t, kAesBlockSize> Value128;
}

namespace
{

Value256 stretch(const StrRef&   password,
                 const Value128& iv)
{
    Value256 digest;

    digest.fill(0);

    std::copy(iv.begin(), iv.end(), digest.begin());

    // Dirty UTF-16LE conversion for 7-bit ASCII.
    std::array<uint8_t, (Config::kPasswordMax * 2)> pwdUtf16;
    std::size_t pwdUtf16Len(0);
    
    for (auto& c : password)
    {
        pwdUtf16[pwdUtf16Len++] = c;
        pwdUtf16[pwdUtf16Len++] = 0;
    }

    // 8192 rounds of SHA256 on the IV and password as per AESCrypt.
    for (int i(0); i < 8192; ++i)
    {
        mbedtls_sha256_context ctx;
        
        mbedtls_sha256_init(&ctx);
        mbedtls_sha256_starts(&ctx, 0);
        mbedtls_sha256_update(&ctx, digest.begin(), digest.size());
        mbedtls_sha256_update(&ctx,
                              pwdUtf16.begin(),
                              pwdUtf16Len);
        mbedtls_sha256_finish(&ctx, digest.begin());
        mbedtls_sha256_free(&ctx);
    }

    return digest;
}

}


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

    auto key(stretch(mPassword, iv));
    
    auto dataIv(mEntropyPool.read128());

    auto dataKey(mEntropyPool.read());

    std::array<uint8_t, dataIv.size() + dataKey.size()> dataIvKey;

    std::copy(dataIv.begin(), dataIv.end(), dataIvKey.begin());
    std::copy(dataKey.begin(), dataKey.end(), dataIvKey.begin() + dataIv.size());
    
    std::array<uint8_t, dataIv.size() + dataKey.size()> dataIvKeyCrypt;

    {
        auto tempIv(iv);
        mbedtls_aes_context ctx;
    
        mbedtls_aes_init(&ctx);
        mbedtls_aes_setkey_enc(&ctx, key.begin(), 256);
        mbedtls_aes_crypt_cbc(&ctx,
                              MBEDTLS_AES_ENCRYPT,
                              dataIvKey.size(),
                              tempIv.begin(),
                              dataIvKey.begin(),
                              dataIvKeyCrypt.begin());
        mbedtls_aes_free(&ctx);
    }

    Value256 dataIvKeyHmac;

    {
        auto mdInfo(mbedtls_md_info_from_type(MBEDTLS_MD_SHA256));

        auto rc(mbedtls_md_hmac(mdInfo,
                                key.begin(),
                                key.size(),
                                dataIvKeyCrypt.begin(),
                                dataIvKeyCrypt.size(),
                                dataIvKeyHmac.begin()));

        if (rc != 0)
        {
            while(1);
        }
    }


    mOutStream.write("AES");
    mOutStream.write(uint8_t('\x02'));
    mOutStream.write(uint8_t('\x00'));

    StrRef createdBy("CREATED_BY");
    StrRef creator("pyAesCrypt 0.3"); // FIXME: Set for testing

    mOutStream.write(uint8_t('\x00'));
    mOutStream.write(static_cast<char>(createdBy.length() + creator.length() + 1));
    mOutStream.write(createdBy);
    mOutStream.write(uint8_t('\x00'));
    mOutStream.write(creator);

    mOutStream.write(uint8_t('\x00'));
    mOutStream.write(uint8_t('\x80'));

    for (int i(0); i < 128; ++i)
    {
        mOutStream.write(uint8_t('\x00'));
    }

    mOutStream.write(uint8_t('\x00'));
    mOutStream.write(uint8_t('\x00'));
    
    mOutStream.write(iv);
    mOutStream.write(dataIvKeyCrypt);
    mOutStream.write(dataIvKeyHmac);

    auto blockCount((mDataOut.position() + kAesBlockSize - 1) / kAesBlockSize);
    auto blockOffset(mDataOut.position() % kAesBlockSize);
    auto cryptSize(blockCount * kAesBlockSize);
    
    std::array<uint8_t, 4096> cryptData;
    
    {
        auto tempDataIv(dataIv);
        mbedtls_aes_context ctx;
    
        mbedtls_aes_init(&ctx);
        mbedtls_aes_setkey_enc(&ctx, dataKey.begin(), 256);
        mbedtls_aes_crypt_cbc(&ctx,
                              MBEDTLS_AES_ENCRYPT,
                              cryptSize,
                              tempDataIv.begin(),
                              mData.begin(),
                              cryptData.begin());
        mbedtls_aes_free(&ctx);
    }

    Value256 cryptDataHmac;

    {
        auto mdInfo(mbedtls_md_info_from_type(MBEDTLS_MD_SHA256));

        mbedtls_md_hmac(mdInfo,
                        dataKey.begin(),
                        dataKey.size(),
                        cryptData.begin(),
                        cryptSize,
                        cryptDataHmac.begin());
    }

    mOutStream.write(DataRef(cryptData.begin(),
                           cryptData.begin() + cryptSize));
    mOutStream.write(uint8_t(blockOffset));
    mOutStream.write(cryptDataHmac);
}

void CryptoOutStream::write(const DataRef& data)
{
    mDataOut.write(data);
}
