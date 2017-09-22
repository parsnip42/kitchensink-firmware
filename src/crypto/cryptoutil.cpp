#include "crypto/cryptoutil.h"

#include "types/strref.h"
#include "config.h"

#include <mbedtls/sha256.h>

namespace CryptoUtil
{

std::array<uint8_t, 32> stretch(const StrRef&                  password,
                                const std::array<uint8_t, 16>& iv)
{
    std::array<uint8_t, 32> digest;

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
