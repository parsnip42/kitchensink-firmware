#include "tablelayout.h"

TableLayout::TableLayout(int titleWidth,
                         int width,
                         int height,
                         int margin)
    : mCurrent(0)
    , mTitleWidth(titleWidth)
    , mWidth(width)
    , mHeight(height)
    , mMargin(margin)

{ }

Rectangle TableLayout::next()
{
    auto current(mCurrent++);
    
    return Rectangle((current % 2) * (mTitleWidth + mMargin),
                     (current / 2) * mHeight,
                     (current % 2) ? (mWidth - (mTitleWidth + mMargin)) : mTitleWidth,
                     mHeight);
}
