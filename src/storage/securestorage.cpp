#include "storage/securestorage.h"
#include "hardware/entropypool.h"
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

SecureStorage::IStream::IStream(InStream&     inStream,
                                const StrRef& password)
    : mInStream(inStream)
    , mPassword(password)
    , mError(Error::kNone)
{
    readHeader();
}

std::size_t SecureStorage::IStream::read(OutStream& os, std::size_t len)
{
    if (mError != Error::kNone)
    {
        return 0;
    }
    
    return 0;
}

void SecureStorage::IStream::readHeader()
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

SecureStorage::OStream::OStream(OutStream&    ostream,
                                const StrRef& password,
                                EntropyPool&  entropyPool)
    : mOStream(ostream)
    , mPassword(password)
    , mEntropyPool(entropyPool)
    , mData()
    , mDataOut(mData)
{ }

SecureStorage::OStream::~OStream()
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


    mOStream.write("AES");
    mOStream.write(uint8_t('\x02'));
    mOStream.write(uint8_t('\x00'));

    StrRef createdBy("CREATED_BY");
    StrRef creator("pyAesCrypt 0.3"); // FIXME: Set for testing

    mOStream.write(uint8_t('\x00'));
    mOStream.write(static_cast<char>(createdBy.length() + creator.length() + 1));
    mOStream.write(createdBy);
    mOStream.write(uint8_t('\x00'));
    mOStream.write(creator);

    mOStream.write(uint8_t('\x00'));
    mOStream.write(uint8_t('\x80'));

    for (int i(0); i < 128; ++i)
    {
        mOStream.write(uint8_t('\x00'));
    }

    mOStream.write(uint8_t('\x00'));
    mOStream.write(uint8_t('\x00'));
    
    mOStream.write(iv);
    mOStream.write(dataIvKeyCrypt);
    mOStream.write(dataIvKeyHmac);

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

    mOStream.write(DataRef(cryptData.begin(),
                           cryptData.begin() + cryptSize));
    mOStream.write(uint8_t(blockOffset));
    mOStream.write(cryptDataHmac);
}

void SecureStorage::OStream::write(const DataRef& data)
{
    mDataOut.write(data);
}
