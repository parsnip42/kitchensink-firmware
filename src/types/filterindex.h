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
    explicit FilterIndex(std::size_t maxElements = Size)
    {
        filter(maxElements,
               [](std::size_t)
               {
                   return true;
               });
    }

public:
    std::size_t operator[](std::size_t index) const
    {
        return static_cast<std::size_t>(mData[index]);
    }

    std::size_t filteredSize() const
    {
        return mSize;
    }
    
    template <typename Func>
    void filter(std::size_t maxElements, const Func& func)
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
    
private:
    std::array<IndexElement, Size> mData;
    std::size_t                    mSize;
};

#endif
