#ifndef INCLUDED_INDEXEDITERATOR_H
#define INCLUDED_INDEXEDITERATOR_H

#include <cstdint>
#include <iterator>

template <typename Data>
class IndexedIterator : public std::iterator<std::bidirectional_iterator_tag, typename Data::value_type>
{
public:
    typedef typename Data::value_type value_type;
    typedef typename Data::reference  reference;
    typedef int                       difference_type;

public:
    explicit IndexedIterator(Data&       data,
                             std::size_t index)
        : mData(data)
        , mIndex(index)
    { }

public:
    typename Data::reference operator*()
    {
        return mData[mIndex];
    }

    IndexedIterator& operator++()
    {
        ++mIndex;

        return *this;
    }
    
    IndexedIterator operator++(int)
    {
        auto prev(*this);
        
        ++(*this);
        
        return prev;
    }
    
    IndexedIterator& operator--()
    {
        --mIndex;
        
        return *this;
    }
    
    IndexedIterator operator--(int)
    {
        auto prev(*this);
        
        --(*this);
        
        return prev;
    }
        
public:
    Data&       mData;
    std::size_t mIndex;

private:
    template <typename Data_>
    friend bool operator==(const IndexedIterator<Data_>& lhs,
                           const IndexedIterator<Data_>& rhs);
};


template <typename Data>
inline
bool operator==(const IndexedIterator<Data>& lhs,
                const IndexedIterator<Data>& rhs)
{
    return (&lhs.mData == &rhs.mData) && (lhs.mIndex == rhs.mIndex);
}

template <typename Data>
inline
bool operator!=(const IndexedIterator<Data>& lhs,
                const IndexedIterator<Data>& rhs)
{
    return !(lhs == rhs);
}

template <typename Data>
inline
IndexedIterator<Data> operator+(const IndexedIterator<Data>& lhs, int n)
{
    return IndexedIterator<Data>(lhs.mData,
                                 lhs.mIndex + n);
}

template <typename Data>
inline
IndexedIterator<Data> operator-(const IndexedIterator<Data>& lhs, int n)
{
    return IndexedIterator<Data>(lhs.mData,
                                 lhs.mIndex - n);
}

#endif










