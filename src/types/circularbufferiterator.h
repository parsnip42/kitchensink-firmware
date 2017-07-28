#ifndef INCLUDED_CIRCULARBUFFERITERATOR_H
#define INCLUDED_CIRCULARBUFFERITERATOR_H

#include <array>
#include <cstdint>
#include <iterator>

template <typename T, std::size_t Capacity>
class CircularBufferIterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
private:
    typedef std::array<T, Capacity> Data;
    
public:
    typedef T  value_type;
    typedef T& reference_type;

public:
    CircularBufferIterator();

private:
    CircularBufferIterator(Data* data,
                           int   index);
        
public:
    T& operator*();
    T* operator->();
    CircularBufferIterator& operator++();
    CircularBufferIterator operator++(int);
    CircularBufferIterator& operator--();
    CircularBufferIterator operator--(int);
    
private:
    Data*       mData;
    std::size_t mIndex;

private:
    template <typename T_, std::size_t Capacity_>
    friend class CircularBuffer;
    
    template <typename T_, std::size_t Capacity_>
    friend bool operator==(const CircularBufferIterator<T_, Capacity_>& lhs,
                           const CircularBufferIterator<T_, Capacity_>& rhs);
};


template <typename T, std::size_t Capacity>
bool operator==(const CircularBufferIterator<T, Capacity>& lhs,
                const CircularBufferIterator<T, Capacity>& rhs)
{
    return (lhs.mData == rhs.mData) &&
        (lhs.mIndex == rhs.mIndex);
}

template <typename T, std::size_t Capacity>
bool operator!=(const CircularBufferIterator<T, Capacity>& lhs,
                const CircularBufferIterator<T, Capacity>& rhs)
{
    return !(lhs == rhs);
}


template <typename T, std::size_t Capacity>
CircularBufferIterator<T, Capacity>::CircularBufferIterator()
    : mData(nullptr)
    , mIndex(0)
{ }

template <typename T, std::size_t Capacity>
CircularBufferIterator<T, Capacity>::CircularBufferIterator(Data* data,
                                                            int   index)
    : mData(data)
    , mIndex(index)
{ }

template <typename T, std::size_t Capacity>
T& CircularBufferIterator<T, Capacity>::operator*()
{
    return (*mData)[mIndex];
}

template <typename T, std::size_t Capacity>
T* CircularBufferIterator<T, Capacity>::operator->()
{
    return &(**this);
}

template <typename T, std::size_t Capacity>
CircularBufferIterator<T, Capacity>& CircularBufferIterator<T, Capacity>::operator++()
{
    mIndex = (mIndex + 1) % Capacity;
    
    return *this;
};
        
template <typename T, std::size_t Capacity>
CircularBufferIterator<T, Capacity> CircularBufferIterator<T, Capacity>::operator++(int)
{
    auto prev(*this);
    
    ++(*this);
    
    return prev;
};

template <typename T, std::size_t Capacity>
CircularBufferIterator<T, Capacity>& CircularBufferIterator<T, Capacity>::operator--()
{
    mIndex = (mIndex + Capacity - 1) % Capacity;
    
    return *this;
};

template <typename T, std::size_t Capacity>
CircularBufferIterator<T, Capacity> CircularBufferIterator<T, Capacity>::operator--(int)
{
    auto prev(*this);
    
    --(*this);
    
    return prev;
};

#endif
