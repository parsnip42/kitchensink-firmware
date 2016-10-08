#ifndef INCLUDED_CIRCULARBUFFER_H
#define INCLUDED_CIRCULARBUFFER_H

#include <array>
#include <cstdint>

template <typename T, std::size_t Capacity>
class CircularBuffer
{
public:
    CircularBuffer();

public:
    std::size_t size() const;
    bool empty() const;
    void push(const T& value);
    T pop();
    
private:
    std::size_t             mStart;
    std::size_t             mEnd;
    bool                    mFull;
    std::array<T, Capacity> mData;
};


template <typename T, std::size_t Capacity>
inline
CircularBuffer<T, Capacity>::CircularBuffer()
    : mStart(0)
    , mEnd(0)
    , mFull(false)
{ }

template <typename T, std::size_t Capacity>
inline
void CircularBuffer<T, Capacity>::push(const T& value)
{
    mData[mEnd] = value;

    mEnd = (mEnd + 1) % Capacity;
    mFull = (mStart == mEnd);
}

template <typename T, std::size_t Capacity>
inline
T CircularBuffer<T, Capacity>::pop()
{
    T value(mData[mStart]);

    mStart = (mStart + 1) % Capacity;
    mFull = false;
    
    return value;
}

template <typename T, std::size_t Capacity>
inline
bool CircularBuffer<T, Capacity>::empty() const
{
    return !mFull && (mStart == mEnd);   
}

template <typename T, std::size_t Capacity>
inline
std::size_t CircularBuffer<T, Capacity>::size() const
{
    if (mFull)
    {
        return Capacity;
    }
    else if (mStart <= mEnd) 
    {
        return mEnd - mStart;
    }
    else
    {
        return (Capacity - mStart) + mEnd;
    }
}

#endif
