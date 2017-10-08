#ifndef INCLUDED_CRYPTOTYPES_H
#define INCLUDED_CRYPTOTYPES_H

#include <array>
#include <cstdint>

namespace Crypto
{

constexpr std::size_t kSHA256Len    = 32;
constexpr std::size_t kHmacLen      = 32;
constexpr std::size_t kAesBlockSize = 16;
constexpr std::size_t kAesKeyLen    = 32;

typedef std::array<uint8_t, kSHA256Len>    SHA256;
typedef std::array<uint8_t, kHmacLen>      HMAC;
typedef std::array<uint8_t, kAesBlockSize> IV;
typedef std::array<uint8_t, kAesKeyLen>    Key;

};

#endif
