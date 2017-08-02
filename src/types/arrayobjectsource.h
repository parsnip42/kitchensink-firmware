#ifndef INCLUDED_ARRAYOBJECTSOURCE_H
#define INCLUDED_ARRAYOBJECTSOURCE_H

#include "types/objectsource.h"

template <typename Type>
class ArrayObjectSource : public ObjectSource<Type>
{
public:
    typedef const Type* const_iterator;
    
public:
    explicit ArrayObjectSource(const_iterator begin,
                               const_iterator end)
        : mBegin(begin)
        , mEnd(end)
    { }

public:
    virtual Type operator[](std::size_t index) const override
    {
        return *(mBegin + index);
    }
    
    virtual std::size_t size() const override
    {
        return mEnd - mBegin;
    }
    
private:
    const_iterator mBegin;
    const_iterator mEnd;
};

#endif
