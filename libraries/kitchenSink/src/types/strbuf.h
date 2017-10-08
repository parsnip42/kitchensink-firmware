#ifndef INCLUDED_STRBUF_H
#define INCLUDED_STRBUF_H

#include "types/strref.h"

#include <array>
#include <cstdint>

template <std::size_t Capacity>
class StrBuf
{
private:
    typedef std::array<char, Capacity> Data;
    
public:
    typedef typename Data::const_iterator const_iterator;
    typedef typename Data::iterator       iterator;

public:
    StrBuf();
    StrBuf(const StrRef& strRef);

public:
    StrBuf<Capacity>& insert(iterator it, char c);
    StrBuf<Capacity>& erase(iterator it);
    
public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;

    iterator begin();
    iterator end();
    
    constexpr std::size_t capacity() const;
    constexpr std::size_t length() const;
    constexpr bool empty() const;

    void clear();
    
public:
    StrBuf<Capacity>& operator=(const StrRef& strRef);
    constexpr operator StrRef() const;

    constexpr const char& operator[](std::size_t n) const;
    char& operator[](std::size_t n);
    
private:
    Data mData;

private:
    static constexpr std::size_t length(const_iterator data);
};


template <std::size_t Capacity>
inline
StrBuf<Capacity>::StrBuf()
{
    mData[0] = '\0';
}

template <std::size_t Capacity>
inline
StrBuf<Capacity>::StrBuf(const StrRef& strRef)
{
    *this = strRef;
}

template <std::size_t Capacity>
inline
StrBuf<Capacity>& StrBuf<Capacity>::insert(iterator it, char c)
{
    auto endIt(end());
    
    std::move_backward(it, endIt + 1, endIt + 2);

    *it = c;

    return *this;
}

template <std::size_t Capacity>
inline
StrBuf<Capacity>& StrBuf<Capacity>::erase(iterator it)
{
    std::move(it + 1, end() + 1, it);
    
    return *this;
}

template <std::size_t Capacity>
inline
void StrBuf<Capacity>::clear()
{
    mData.front() = '\0';
}

template <std::size_t Capacity>
inline
constexpr typename StrBuf<Capacity>::const_iterator StrBuf<Capacity>::begin() const
{
    return mData.begin();
}

template <std::size_t Capacity>
inline
constexpr typename StrBuf<Capacity>::const_iterator StrBuf<Capacity>::end() const
{
    return mData.begin() + length();
}

template <std::size_t Capacity>
inline
typename StrBuf<Capacity>::iterator StrBuf<Capacity>::begin()
{
    return mData.begin();
}

template <std::size_t Capacity>
inline
typename StrBuf<Capacity>::iterator StrBuf<Capacity>::end()
{
    return mData.begin() + length();
}

template <std::size_t Capacity>
inline
constexpr std::size_t StrBuf<Capacity>::length() const
{
    return length(mData.begin());
}

template <std::size_t Capacity>
inline
constexpr bool StrBuf<Capacity>::empty() const
{
    return mData.front() == '\0';
}

template <std::size_t Capacity>
inline
constexpr std::size_t StrBuf<Capacity>::capacity() const
{
    return mData.size() - 1;
}

template <std::size_t Capacity>
inline
StrBuf<Capacity>& StrBuf<Capacity>::operator=(const StrRef& strRef)
{
    *std::copy(strRef.begin(),
               strRef.begin() + std::min(strRef.length(), capacity()),
               mData.begin()) = '\0';
    
    return *this;
}

template <std::size_t Capacity>
inline
constexpr StrBuf<Capacity>::operator StrRef() const
{
    return StrRef(mData.begin());
}

template <std::size_t Capacity>
inline
constexpr const char& StrBuf<Capacity>::operator[](std::size_t n) const
{
    return mData[n];
}

template <std::size_t Capacity>
inline
char& StrBuf<Capacity>::operator[](std::size_t n)
{
    return mData[n];
}

template <std::size_t Capacity>
inline
constexpr std::size_t StrBuf<Capacity>::length(const_iterator data)
{
    return (*data == '\0') ? 0 : (1 + length(data + 1));
}

#endif
