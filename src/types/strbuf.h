#ifndef INCLUDED_STRBUF_H
#define INCLUDED_STRBUF_H

#include "types/strref.h"

#include <cstdio>
#include <cstdint>
#include <cstring>

namespace Types
{

template <std::size_t Size>
class StrBuf
{
public:
    typedef const char* const_iterator;
    
public:
    constexpr StrBuf();
    StrBuf(const StrRef& strRef);

public:
    StrBuf<Size>& appendStr(const StrRef& str);
    StrBuf<Size>& appendChar(char c);
    StrBuf<Size>& appendInt(int n);
    StrBuf<Size>& popEnd();
    
public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;
    constexpr std::size_t size() const;
    constexpr bool empty() const;

public:
    StrBuf<Size>& operator=(const StrRef& strRef);
    constexpr operator StrRef() const;

private:
    constexpr std::size_t size(const char* data) const;

private:
    char mData[Size];
};


template <std::size_t Size>
inline
constexpr StrBuf<Size>::StrBuf()
    : mData{0}
{ }

template <std::size_t Size>
inline
StrBuf<Size>::StrBuf(const StrRef& strRef)
{
    strlcpy(mData, strRef.begin(), sizeof(mData));
}

template <std::size_t Size>
inline
StrBuf<Size>& StrBuf<Size>::appendStr(const StrRef& str)
{
    auto currentSize(size());

    strlcpy(mData + currentSize,
            str.begin(),
            sizeof(mData) - currentSize);
    
    return *this;
}

template <std::size_t Size>
inline
StrBuf<Size>& StrBuf<Size>::appendChar(char c)
{
    auto currentSize(size());

    if (currentSize < Size - 1)
    {
        mData[currentSize] = c;
        mData[currentSize + 1] = '\0';
    }

    return *this;
}

template <std::size_t Size>
inline
StrBuf<Size>& StrBuf<Size>::appendInt(int n)
{
    auto currentSize(size());

    snprintf(mData + currentSize, Size - currentSize, "%d", n);

    return *this;
}

template <std::size_t Size>
inline
StrBuf<Size>& StrBuf<Size>::popEnd()
{
    if (!empty())
    {
        mData[size() - 1] = '\0';
    }
    
    return *this;
}

template <std::size_t Size>
inline
constexpr typename StrBuf<Size>::const_iterator StrBuf<Size>::begin() const
{
    return mData;
}

template <std::size_t Size>
inline
constexpr typename StrBuf<Size>::const_iterator StrBuf<Size>::end() const
{
    return mData + size();
}

template <std::size_t Size>
inline
constexpr std::size_t StrBuf<Size>::size() const
{
    return size(mData);
}

template <std::size_t Size>
inline
constexpr bool StrBuf<Size>::empty() const
{
    return (mData[0] == '\0');
}

template <std::size_t Size>
inline
StrBuf<Size>& StrBuf<Size>::operator=(const StrRef& strRef)
{
    strlcpy(mData, strRef.begin(), sizeof(mData));

    return *this;
}

template <std::size_t Size>
inline
constexpr StrBuf<Size>::operator StrRef() const
{
    return StrRef(mData);
}

template <std::size_t Size>
inline
constexpr std::size_t StrBuf<Size>::size(const char* data) const
{
    return (data[0] == '\0') ? 0 : (1 + size(data + 1));
}

}

#endif
