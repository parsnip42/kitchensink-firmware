#ifndef INCLUDED_ARRAYOUTSTREAM_H
#define INCLUDED_ARRAYOUTSTREAM_H

#include "types/outstream.h"

#include <array>
#include <cstdint>

class DataRef;

class ArrayOutStream : public OutStream
{
public:
    template <std::size_t Capacity>
    ArrayOutStream(std::array<uint8_t, Capacity>& array);

public:
    virtual void write(const DataRef& data) override;

public:
    std::size_t position() const;

private:
    uint8_t*    mData;
    std::size_t mCapacity;
    std::size_t mPosition;
};


template <std::size_t Capacity>
inline
ArrayOutStream::ArrayOutStream(std::array<uint8_t, Capacity>& array)
    : mData(array.begin())
    , mCapacity(Capacity)
    , mPosition(0)
{ }

inline
std::size_t ArrayOutStream::position() const
{
    return mPosition;
}

#endif
