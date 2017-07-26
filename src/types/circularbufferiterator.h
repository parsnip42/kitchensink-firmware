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
    typedef T                               value_type;
    typedef T&                              reference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef std::size_t                     distance_type;
        
private:
    CircularBufferIterator(Data*       data,
                           std::size_t index)
        : mData(data)
        , mIndex(index)
    { }
        
public:
    reference_type operator*()
    {
        return (*mData)[mIndex];
    }
        
    CircularBufferIterator& operator++()
    {
        mIndex = (mIndex + 1) % Capacity;

        return *this;
    };
        
    CircularBufferIterator operator++(int)
    {
        auto prev(*this);

        ++(*this);

        return prev;
    };

    CircularBufferIterator& operator--()
    {
        mIndex = (mIndex - 1) % Capacity;

        return *this;
    };
        
    CircularBufferIterator operator--(int)
    {
        auto prev(*this);

        --(*this);

        return prev;
    };

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
    return lhs.mIndex == rhs.mIndex;
}

template <typename T, std::size_t Capacity>
bool operator!=(const CircularBufferIterator<T, Capacity>& lhs,
                const CircularBufferIterator<T, Capacity>& rhs)
{
    return !(lhs == rhs);
}

#endif
