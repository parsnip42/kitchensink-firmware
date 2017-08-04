#ifndef INCLUDED_MAPPEDOBJECTSOURCE_H
#define INCLUDED_MAPPEDOBJECTSOURCE_H

#include "types/objectsource.h"

#include <type_traits>

template <typename Type, typename Data>
class MappedObjectSource : public ObjectSource<Type>
{
public:
    typedef Type value_type;
    typedef value_type (*Func)(decltype(std::declval<const Data>()[0]), std::size_t);

public:
    MappedObjectSource(const Data& data,
                       const Func& func);

public:
    virtual value_type operator[](std::size_t index) const override;
    virtual std::size_t size() const override;

private:
    const Data& mData;
    Func        mFunc;
};


template <typename Type, typename Data>
inline
MappedObjectSource<Type, Data>::MappedObjectSource(const Data& data,
                                                   const Func& func)
    : mData(data)
    , mFunc(func)
{ }

template <typename Type, typename Data>
inline
typename MappedObjectSource<Type, Data>::value_type MappedObjectSource<Type, Data>::operator[](std::size_t index) const
{
    return mFunc(mData[index], index);
}

template <typename Type, typename Data>
inline
std::size_t MappedObjectSource<Type, Data>::size() const
{
    return mData.size();
}

#endif
