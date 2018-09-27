#include "crypto/cryptoutil.h"

#include "types/dataref.h"
#include "types/strbuf.h"
#include "config.h"

#include <mbedTLS_AES.h>
#include <mbedTLS_SHA256.h>
#include <mbedTLS_MD.h>

namespace CryptoUtil
{

HMACContext::HMACContext()
    : mContextInitialized(false)
{ }

HMACContext::~HMACContext()
{
    if (mContextInitialized)
    {
        mbedtls_md_free(&mContext);
    }
}

void HMACContext::init(const Crypto::Key& key)
{
    mbedtls_md_setup(&mContext,
                     mbedtls_md_info_from_type(MBEDTLS_MD_SHA256),
                     1);
    
    mbedtls_md_hmac_starts(&mContext, key.begin(), key.size());

    mContextInitialized = true;
}

void HMACContext::update(const DataRef& data)
{
    mbedtls_md_hmac_update(&mContext, data.begin(), data.size());
}

Crypto::HMAC HMACContext::finish()
{
    Crypto::HMAC hmac;

    mbedtls_md_hmac_finish(&mContext, hmac.begin());
    mbedtls_md_free(&mContext);

    mContextInitialized = false;
        
    return hmac;
}

Crypto::SHA256 sha256(const uint8_t* begin,
                      const uint8_t* end)
{
    Crypto::SHA256 output;

    mbedtls_sha256(begin, end - begin, output.begin(), 0);

    return output;
}

Crypto::Key stretch(const StrRef&     password,
                    const Crypto::IV& iv)
{
    Crypto::Key digest;

    digest.fill(0);

    std::copy(iv.begin(), iv.end(), digest.begin());
    
    // Dirty UTF-16LE conversion for 7-bit ASCII.
    std::array<uint8_t, (Config::kPasswordMax + Config::kPasswordSuffix.length()) * 2> pwdUtf16;
    std::size_t pwdUtf16Len(0);
    
    for (auto& c : password)
    {
        pwdUtf16[pwdUtf16Len++] = c;
        pwdUtf16[pwdUtf16Len++] = 0;
    }
    
    // Also, concatenate the firmware password suffix onto the end.
    for (auto& c : Config::kPasswordSuffix)
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

Crypto::HMAC hmac(const Crypto::Key& key,
                  const uint8_t*     begin,
                  const uint8_t*     end)
{
    HMACContext hmac;

    hmac.init(key);
    hmac.update(DataRef(begin, end));
    
    return hmac.finish();
}

Crypto::IV encrypt(const Crypto::Key& key,
                   const Crypto::IV&  iv,
                   std::size_t        size,
                   const uint8_t*     source,
                   uint8_t*           dest)
{
    auto nextIv(iv);
    mbedtls_aes_context ctx;
    
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_enc(&ctx, key.begin(), 256);
    mbedtls_aes_crypt_cbc(&ctx,
                          MBEDTLS_AES_ENCRYPT,
                          size,
                          nextIv.begin(),
                          source,
                          dest);
    mbedtls_aes_free(&ctx);

    return nextIv;
}

Crypto::IV decrypt(const Crypto::Key& key,
                   const Crypto::IV&  iv,
                   std::size_t        size,
                   const uint8_t*     source,
                   uint8_t*           dest)
{
    auto nextIv(iv);
    mbedtls_aes_context ctx;
    
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_dec(&ctx, key.begin(), 256);
    mbedtls_aes_crypt_cbc(&ctx,
                          MBEDTLS_AES_DECRYPT,
                          size,
                          nextIv.begin(),
                          source,
                          dest);
    mbedtls_aes_free(&ctx);

    return nextIv;
}

}
