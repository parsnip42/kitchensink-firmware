#ifndef INCLUDED_CRYPTOUTIL_H
#define INCLUDED_CRYPTOUTIL_H

#include "crypto/cryptotypes.h"

#include <array>
#include <cstdint>

class StrRef;

namespace CryptoUtil
{
Crypto::SHA256 sha256(const uint8_t* begin,
                      const uint8_t* end);

Crypto::Key stretch(const StrRef&     password,
                    const Crypto::IV& iv);

Crypto::HMAC hmac(const Crypto::Key& key,
                  const uint8_t*     begin,
                  const uint8_t*     end);

void encrypt(const Crypto::Key& key,
             const Crypto::IV&  iv,
             std::size_t        size,
             const uint8_t*     source,
             uint8_t*           dest);

void decrypt(const Crypto::Key& key,
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
void encrypt(const Crypto::Key&                   key,
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
void decrypt(const Crypto::Key&                   key,
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
