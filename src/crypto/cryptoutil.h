#ifndef INCLUDED_CRYPTOUTIL_H
#define INCLUDED_CRYPTOUTIL_H

#include <array>
#include <cstdint>

class StrRef;

namespace CryptoUtil
{

std::array<uint8_t, 32> stretch(const StrRef&                  password,
                                const std::array<uint8_t, 16>& iv);

}

#endif
