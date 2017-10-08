#ifndef INCLUDED_BITMASKATTRIBUTES_H
#define INCLUDED_BITMASKATTRIBUTES_H

#include <cstddef>
#include <cstdint>

template <std::size_t Size>
struct BitmaskAttributes;

template<>
struct BitmaskAttributes<8>
{
    typedef uint8_t Data;
};

template<>
struct BitmaskAttributes<16>
{
    typedef uint16_t Data;
};

template<>
struct BitmaskAttributes<32>
{
    typedef uint32_t Data;
};

template<>
struct BitmaskAttributes<64>
{
    typedef uint64_t Data;
};

template <std::size_t Size>
struct BitmaskAttributes
{
    typedef typename BitmaskAttributes<Size + 1>::Data Data;
};

#endif
