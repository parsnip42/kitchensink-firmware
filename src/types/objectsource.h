#ifndef INCLUDED_OBJECTSOURCE_H
#define INCLUDED_OBJECTSOURCE_H

#include <cstdint>

template <typename T>
class ObjectSource
{
public:
    virtual void item(T& item, std::size_t index) const = 0;
    virtual std::size_t size() const = 0;
};

#endif
