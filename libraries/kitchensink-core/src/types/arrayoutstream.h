#ifndef INCLUDED_ARRAYOUTSTREAM_H
#define INCLUDED_ARRAYOUTSTREAM_H

#include "types/outstream.h"
#include "types/dataref.h"

#include <array>
#include <cstdint>

class DataRef;

class ArrayOutStream : public OutStream
{
public:
    template <std::size_t Capacity>
    ArrayOutStream(std::array<uint8_t, Capacity>& array);

public:
    virtual std::size_t write(const DataRef& data) override;

public:
    DataRef data() const;
    std::size_t position() const;
    std::size_t remaining() const;
    void reset();
    
private:
    uint8_t*    mData;
    std::size_t mCapacity;
    std::size_t mPosition;

private:
    ArrayOutStream(const ArrayOutStream&) = delete;
    ArrayOutStream& operator=(const ArrayOutStream&) = delete;
};


template <std::size_t Capacity>
inline
ArrayOutStream::ArrayOutStream(std::array<uint8_t, Capacity>& array)
    : mData(array.begin())
    , mCapacity(Capacity)
    , mPosition(0)
{ }

inline
DataRef ArrayOutStream::data() const
{
    return DataRef(mData, mData + mPosition);
}

inline
std::size_t ArrayOutStream::position() const
{
    return mPosition;
}

inline
std::size_t ArrayOutStream::remaining() const
{
    return mCapacity - mPosition;
}

inline
void ArrayOutStream::reset()
{
    mPosition = 0;
}

#endif
