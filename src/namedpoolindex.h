#ifndef INCLUDED_POOLINDEX_H
#define INCLUDED_POOLINDEX_H

#include "poolindexentry.h"
#include "types/strbuf.h"

#include <array>
#include <cstdint>

template <typename Iterator, typename std::size_t Capacity>
class NamedPoolIndex
{
public:
    static constexpr std::size_t kCapacity = Capacity;

public:
    class Entry
    {
    public:
        constexpr Entry();
        
    public:
        constexpr bool empty() const;
        
    public:
        Iterator          begin;
        Iterator          end;
        Types::StrBuf<24> name;
        
    private:
        Entry(const Entry&) = delete;
        Entry& operator=(const Entry&) = delete;
    };

private:
    typedef std::array<Entry, Capacity> Index;

public:
    constexpr NamedPoolIndex() = default;

public:
    void shift(const Iterator& point, int32_t shift);
    
public:
    const Entry& operator[](int index) const;
    Entry& operator[](int index);

private:
    Index mIndex;
};


template <typename Iterator, typename std::size_t Capacity>
inline
constexpr NamedPoolIndex<Iterator, Capacity>::Entry::Entry()
    : begin(0)
    , end(0)
{ }

template <typename Iterator, typename std::size_t Capacity>
inline
constexpr bool NamedPoolIndex<Iterator, Capacity>::Entry::empty() const
{
    return (begin == end);
}

template <typename Iterator, typename std::size_t Capacity>
inline
void NamedPoolIndex<Iterator, Capacity>::shift(const Iterator& point, int32_t shift)
{
    for (auto& entry : mIndex)
    {
        if (entry.begin > point)
        {
            entry.begin += shift;
            entry.end += shift;
        }
    }
}

template <typename Iterator, typename std::size_t Capacity>
inline
const typename NamedPoolIndex<Iterator, Capacity>::Entry& NamedPoolIndex<Iterator, Capacity>::operator[](int index) const
{
    return mIndex[index];
}
    
template <typename Iterator, typename std::size_t Capacity>
inline
typename NamedPoolIndex<Iterator, Capacity>::Entry& NamedPoolIndex<Iterator, Capacity>::operator[](int index)
{
    return mIndex[index];
}

#endif
