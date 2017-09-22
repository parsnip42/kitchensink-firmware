#include "crypto/cryptoutil.h"

#include "types/strref.h"
#include "config.h"

#include <mbedtls/aes.h>
#include <mbedtls/sha256.h>
#include <mbedtls/md.h>

namespace CryptoUtil
{

Crypto::Key stretch(const StrRef&     password,
                    const Crypto::IV& iv)
{
    Crypto::Key digest;

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

Crypto::HMAC hmac(const Crypto::Key& key,
                  const uint8_t*     begin,
                  const uint8_t*     end)
{
    auto mdInfo(mbedtls_md_info_from_type(MBEDTLS_MD_SHA256));

    Crypto::HMAC output;
    
    mbedtls_md_hmac(mdInfo,
                    key.begin(),
                    key.size(),
                    begin,
                    end - begin,
                    output.begin());

    return output;
}

void decrypt(const Crypto::Key& key,
             const Crypto::IV&  iv,
             std::size_t        size,
             const uint8_t*     source,
             uint8_t*           dest)
{
    auto tempIv(iv);
    mbedtls_aes_context ctx;
    
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_dec(&ctx, key.begin(), 256);
    mbedtls_aes_crypt_cbc(&ctx,
                          MBEDTLS_AES_DECRYPT,
                          size,
                          tempIv.begin(),
                          source,
                          dest);
    mbedtls_aes_free(&ctx);
}

}
