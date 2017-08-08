#ifndef INCLUDED_FILTERINDEX_H
#define INCLUDED_FILTERINDEX_H

#include <array>
#include <cstdint>

template <std::size_t Size>
class FilterIndex
{
private:
    typedef uint16_t IndexElement;
    
public:
    explicit FilterIndex(std::size_t maxElements = Size);

public:
    std::size_t operator[](std::size_t index) const;

    std::size_t filteredSize() const;
    
    template <typename Func>
    void filter(std::size_t maxElements, const Func& func);
    
private:
    std::array<IndexElement, Size> mData;
    std::size_t                    mSize;
};


template <std::size_t Size>
inline
FilterIndex<Size>::FilterIndex(std::size_t maxElements)
{
    filter(maxElements,
           [](std::size_t)
           {
               return true;
           });
}

template <std::size_t Size>
inline
std::size_t FilterIndex<Size>::operator[](std::size_t index) const
{
    return static_cast<std::size_t>(mData[index]);
}

template <std::size_t Size>
inline
std::size_t FilterIndex<Size>::filteredSize() const
{
    return mSize;
}

template <std::size_t Size>
template <typename Func>
inline
void FilterIndex<Size>::filter(std::size_t maxElements, const Func& func)
{
    std::size_t index(0);
        
    for (std::size_t i(0); i < std::min(Size, maxElements); ++i)
    {
        if (func(i))
        {
            mData[index++] = i;
        }
    }

    mSize = index;
}

#endif
