#ifndef INCLUDED_CIRCULARSTREAM_H
#define INCLUDED_CIRCULARSTREAM_H

#include "types/dataref.h"
#include "types/instream.h"
#include "types/outstream.h"

template <std::size_t Capacity>
class CircularStream : public InStream, public OutStream
{
public:
    typedef std::array<uint8_t, Capacity> Data;

public:
    constexpr CircularStream();

public:
    virtual std::size_t read(OutStream& os, std::size_t len);
    virtual std::size_t write(const DataRef& data);

    constexpr std::size_t size() const;
    constexpr std::size_t remaining() const;
    constexpr bool empty() const;
    
private:
    Data        mData;
    std::size_t mStart;
    std::size_t mEnd;
    bool        mFull;
};


template <std::size_t Capacity>
inline
constexpr CircularStream<Capacity>::CircularStream()
    : mStart(0)
    , mEnd(0)
    , mFull(false)
{ }

template <std::size_t Capacity>
inline
std::size_t CircularStream<Capacity>::read(OutStream& os, std::size_t len)
{
    std::size_t read(0);

    while (!empty() && read < len)
    {
        auto value(mData[mStart]);

        os.write(DataRef(value));
        mStart = (mStart + 1) % Capacity;
        mFull = false;

        ++read;
    }

    return read;
}

template <std::size_t Capacity>
inline
std::size_t CircularStream<Capacity>::write(const DataRef& data)
{
    std::size_t read(0);
    
    while (!mFull && read < data.size())
    {
        mData[mEnd] = data[read++];
        mEnd = (mEnd + 1) % Capacity;
        mFull = (mStart == mEnd);
    }

    return read;
}
    
template <std::size_t Capacity>
inline
constexpr std::size_t CircularStream<Capacity>::size() const
{
    return mFull ?
        Capacity :
        ((mStart <= mEnd) ?
            (mEnd - mStart) :
            ((Capacity - mStart) + mEnd));
}

template <std::size_t Capacity>
inline
constexpr bool CircularStream<Capacity>::empty() const
{
    return !mFull && (mStart == mEnd);   
}

template <std::size_t Capacity>
inline
constexpr std::size_t CircularStream<Capacity>::remaining() const
{
    return Capacity - size();
}
#endif
