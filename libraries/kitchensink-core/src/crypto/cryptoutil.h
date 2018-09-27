#ifndef INCLUDED_CRYPTOUTIL_H
#define INCLUDED_CRYPTOUTIL_H

#include "crypto/cryptotypes.h"

#include <array>
#include <cstdint>

#include <mbedTLS_MD.h>

class DataRef;
class StrRef;

namespace CryptoUtil
{

class HMACContext
{
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


Crypto::SHA256 sha256(const uint8_t* begin,
                      const uint8_t* end);

Crypto::Key stretch(const StrRef&     password,
                    const Crypto::IV& iv);

Crypto::HMAC hmac(const Crypto::Key& key,
                  const uint8_t*     begin,
                  const uint8_t*     end);

Crypto::IV encrypt(const Crypto::Key& key,
                   const Crypto::IV&  iv,
                   std::size_t        size,
                   const uint8_t*     source,
                   uint8_t*           dest);

Crypto::IV decrypt(const Crypto::Key& key,
                   const Crypto::IV&  iv,
                   std::size_t        size,
                   const uint8_t*     source,
                   uint8_t*           dest);


template <std::size_t Capacity>
inline
Crypto::SHA256 sha256(const std::array<uint8_t, Capacity>& data)
{
    return sha256(data.begin(),
                  data.end());
}

template <std::size_t Capacity>
inline
Crypto::HMAC hmac(const Crypto::Key&                   key,
                  const std::array<uint8_t, Capacity>& data)
{
    return hmac(key,
                data.begin(),
                data.end());
}

template <std::size_t Capacity>
inline
Crypto::IV encrypt(const Crypto::Key&                   key,
                   const Crypto::IV&                    iv,
                   const std::array<uint8_t, Capacity>& source,
                   std::array<uint8_t, Capacity>&       dest)
{
    return encrypt(key,
                   iv,
                   Capacity,
                   source.begin(),
                   dest.begin());
}

template <std::size_t Capacity>
inline
Crypto::IV decrypt(const Crypto::Key&                   key,
                   const Crypto::IV&                    iv,
                   const std::array<uint8_t, Capacity>& source,
                   std::array<uint8_t, Capacity>&       dest)
{
    return decrypt(key,
                   iv,
                   Capacity,
                   source.begin(),
                   dest.begin());
}

}

#endif
