#ifndef INCLUDED_SCREENSTACK_H
#define INCLUDED_SCREENSTACK_H

#include "screenid.h"

#include <array>

class ScreenStack
{
private:
    typedef std::array<ScreenId, 10> Data;

public:
    typedef Data::const_iterator const_iterator;
    
public:
    ScreenStack();

public:
    const ScreenId& top() const;
    bool empty() const;
    bool full() const;
    
    void push(const ScreenId& screenId);
    void pop();

    bool dirty();

public:
    const_iterator begin() const;
    const_iterator end() const;
    
private:
    Data        mData;
    std::size_t mSize;
    bool        mDirty;
};


inline
ScreenStack::ScreenStack()
    : mSize(0)
{ }

inline
const ScreenId& ScreenStack::top() const
{
    return mData[mSize - 1];
}

inline
bool ScreenStack::empty() const
{
    return mSize == 0;
}

inline
bool ScreenStack::full() const
{
    return mSize >= mData.size();
}

inline
void ScreenStack::push(const ScreenId& screenId)
{
    mData[mSize++] = screenId;
    mDirty = true;
}

inline
void ScreenStack::pop()
{
    if (mSize > 0)
    {
        --mSize;
        mDirty = true;
    }
}

inline
bool ScreenStack::dirty()
{
    if (mDirty)
    {
        mDirty = false;
        return true;
    }

    return false;
}

inline
ScreenStack::const_iterator ScreenStack::begin() const
{
    return mData.begin();
}

inline
ScreenStack::const_iterator ScreenStack::end() const
{
    return mData.begin() + mSize;
}


#endif
