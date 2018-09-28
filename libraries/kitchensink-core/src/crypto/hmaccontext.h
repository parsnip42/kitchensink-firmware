#ifndef INCLUDED_HMACCONTEXT_H
#define INCLUDED_HMACCONTEXT_H

#include "crypto/cryptotypes.h"
#include "types/dataref.h"

#include <mbedTLS_MD.h>

class HMACContext
{
public:
    static Crypto::HMAC generate(const Crypto::Key& key,
                                 const DataRef& data);
    
public:
    HMACContext();
    ~HMACContext();
    
public:
    void init(const Crypto::Key& key);
    void update(const DataRef& data);
    Crypto::HMAC finish();
    
private:
    bool                 mContextInitialized;
    mbedtls_md_context_t mContext;
};

#endif
