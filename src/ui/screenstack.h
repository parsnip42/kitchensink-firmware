#ifndef INCLUDED_SCREENSTACK_H
#define INCLUDED_SCREENSTACK_H

#include "screenid.h"

#include <array>

class ScreenStack
{
public:
    ScreenStack();

public:
    const ScreenId& top() const;
    bool empty() const;
    
    void push(const ScreenId& screenId);
    void pop();

    bool dirty();
    
private:
    std::array<ScreenId, 10> mData;
    std::size_t              mSize;
    bool                     mDirty;
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

#endif
