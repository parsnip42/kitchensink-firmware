#ifndef INCLUDED_BITITERATOR_H
#define INCLUDED_BITITERATOR_H

#include <cstdint>

template <typename Data>
class BitIterator
{
public:
    explicit BitIterator(const Data& data);

public:
    std::size_t next();
    bool more() const;
    
private:
    Data        mData;
    std::size_t mNextSetBit;
};


template <typename Data>
inline
BitIterator<Data>::BitIterator(const Data& data)
    : mData(data)
    , mNextSetBit(0)
{ }

template <typename Data>
inline
std::size_t BitIterator<Data>::next()
{
    while (!(mData & 1))
    {
        ++mNextSetBit;
        mData >>= 1;
    }
    
    mData >>= 1;

    return mNextSetBit++;
}

template <typename Data>
inline
bool BitIterator<Data>::more() const
{
    return mData != 0;
}

#endif /* INCLUDED_BITITERATOR_H */
