#include "crypto/hmaccontext.h"

Crypto::HMAC HMACContext::generate(const Crypto::Key& key,
                                   const DataRef&     data)
{
    HMACContext hmac;

    hmac.init(key);
    hmac.update(data);
    
    return hmac.finish();
}

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

