#ifndef INCLUDED_ENTROPYPOOL_H
#define INCLUDED_ENTROPYPOOL_H

#include <array>

class EntropyPool
{
private:
    typedef std::array<uint8_t, 1024> Data;
    
public:
    EntropyPool() = default;

public:
    void insert(uint8_t value);
    
private:
    Data mData;
    int  mCount;
};

#endif
