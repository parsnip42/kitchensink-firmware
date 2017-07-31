#ifndef INCLUDED_UI4ARRAY_H
#define INCLUDED_UI4ARRAY_H

#include "types/range.h"

#include <algorithm>
#include <array>
#include <cstdint>

template <std::size_t Size>
class UI4Array
{
private:
    static constexpr std::size_t kNibbleLen       = 4;
    static constexpr uint8_t     kNibbleMask      = (1u << kNibbleLen) - 1;
    static constexpr std::size_t kElementsPerByte = 8 / kNibbleLen;
    static constexpr std::size_t kByteSize        = Size / kElementsPerByte;
    
private:
    typedef std::array<uint8_t, kByteSize> Data;

public:
    typedef Range<typename Data::const_iterator> RawData;
    
public:
    class reference
    {
    private:
        constexpr reference(Data&       data,
                            std::size_t index);

    public:
        // constexpr operator uint8_t() const;
        reference& operator=(uint8_t value);
        
    private:
        Data&       mData;
        std::size_t mIndex;

    private:
        friend class UI4Array;
    };

public:
    UI4Array();

public:
    constexpr std::size_t size() const;
    void clear();
    RawData rawData() const;
    
public:
    // constexpr uint8_t operator[](std::size_t index) const;
    reference operator[](std::size_t index);
    
public:
    Data mData;
};


template <std::size_t Size>
inline
constexpr UI4Array<Size>::reference::reference(Data&       data,
                                               std::size_t index)
    : mData(data)
    , mIndex(index)
{ }

// template <std::size_t Size>
// inline
// constexpr UI4Array<Size>::reference::operator uint8_t() const
// {
//     return (mData[mIndex >> 1] >> ((mIndex & 1) * 4)) & 0xf;
// }

template <std::size_t Size>
inline
typename UI4Array<Size>::reference& UI4Array<Size>::reference::operator=(uint8_t value)
{
    // Compiler should optimise this into something sensible.
    
    value &= kNibbleMask;
    
    auto valueOffset(((kElementsPerByte - 1) - (mIndex % kElementsPerByte)) * kNibbleLen);
    auto& rawByte(mData[mIndex / kElementsPerByte]);

    rawByte &= ~(kNibbleMask << valueOffset);
    rawByte |= value << valueOffset;

    return *this;
}


template <std::size_t Size>
inline
UI4Array<Size>::UI4Array()
{
    clear();
}

template <std::size_t Size>
inline
constexpr std::size_t UI4Array<Size>::size() const
{
    return Size * 2;
}

template <std::size_t Size>
inline
void UI4Array<Size>::clear()
{
    std::fill(mData.begin(),
              mData.end(),
              0);
}

// template <std::size_t Size>
// inline
// constexpr uint8_t UI4Array<Size>::operator[](std::size_t index) const
// {
//     return 0xf;//(mData[index >> 1] >> ((index & 1) * 4)) & 0xf;
// }

template <std::size_t Size>
inline
typename UI4Array<Size>::reference UI4Array<Size>::operator[](std::size_t index)
{
    return reference(mData, index);
}


template <std::size_t Size>
inline
typename UI4Array<Size>::RawData UI4Array<Size>::rawData() const
{
    return RawData(mData.begin(), mData.end());
}

#endif

