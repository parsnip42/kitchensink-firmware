#ifndef INCLUDED_GPIOKEYSET_H
#define INCLUDED_GPIOKEYSET_H

#include "crypto/entropypool.h"
#include "types/bitmask2d.h"
#include "types/range.h"

#include <array>
#include <cstdint>

class GPIOKeySet
{
public:
    typedef const uint8_t* const_iterator;
    
public:
    GPIOKeySet(const_iterator pinsBegin,
               const_iterator pinsEnd);
        
public:
    template <std::size_t Columns, std::size_t Rows>
    void scan(Bitmask2d<Columns, Rows>& keyMask);

private:
    bool readPin(uint8_t pin) const;
        
private:
    Range<const_iterator> mPins;

private:
    GPIOKeySet(const GPIOKeySet&);
    GPIOKeySet& operator=(const GPIOKeySet&);
};


template <std::size_t Columns, std::size_t Rows>
inline
void GPIOKeySet::scan(Bitmask2d<Columns, Rows>& keyMask)
{
    std::size_t column(0);
    
    for (auto pin : mPins)
    {
        keyMask[0][column++] = readPin(pin);
    }
}

#endif
