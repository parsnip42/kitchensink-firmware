#ifndef INCLUDED_ARRAYOBJECTSOURCE_H
#define INCLUDED_ARRAYOBJECTSOURCE_H

#include "types/objectsource.h"

template <typename Array>
class ArrayObjectSource : public ObjectSource<typename Array::value_type>
{
public:
    explicit ArrayObjectSource(Array& array)
        : mArray(array)
    { }

public:
    virtual void item(typename Array::value_type& item,
                      std::size_t                 index) const
    {
        item = mArray[index];
    }
    
    virtual std::size_t size() const
    {
        return mArray.size();
    }
    
private:
    const Array& mArray;
};

#endif
