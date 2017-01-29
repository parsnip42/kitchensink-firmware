#ifndef INCLUDED_POOLINDEXENTRY_H
#define INCLUDED_POOLINDEXENTRY_H

template <typename Iterator, typename Data>
class PoolIndexEntry
{
public:
    constexpr PoolIndexEntry();
    
    constexpr PoolIndexEntry(const Iterator& nBegin,
                             const Iterator& nEnd);

public:
    constexpr bool empty() const;
    void shift(const Iterator& point, int shift);
        
public:
    Iterator begin;
    Iterator end;
    Data     data;
};


template <typename Iterator, typename Data>
inline
constexpr PoolIndexEntry<Iterator, Data>::PoolIndexEntry()
    : begin(0)
    , end(0)
{ }

template <typename Iterator, typename Data>
inline
constexpr PoolIndexEntry<Iterator, Data>::PoolIndexEntry(const Iterator& nBegin,
                                               const Iterator& nEnd)
    : begin(nBegin)
    , end(nEnd)
{ }

template <typename Iterator, typename Data>
inline
constexpr bool PoolIndexEntry<Iterator, Data>::empty() const
{
    return (begin == end);
}

template <typename Iterator, typename Data>
inline
void PoolIndexEntry<Iterator, Data>::shift(const Iterator& point, int shift)
{
    if (begin > point)
    {
        begin += shift;
        end += shift;
    }
}

#endif
