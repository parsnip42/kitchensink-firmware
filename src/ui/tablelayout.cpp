#include "tablelayout.h"

TableLayout::TableLayout(int titleWidth,
                         int width,
                         int height,
                         int marginX,
                         int marginY)
    : mCurrent(0)
    , mTitleWidth(titleWidth)
    , mWidth(width)
    , mHeight(height)
    , mMarginX(marginX)
    , mMarginY(marginY)

{ }

Rectangle TableLayout::next()
{
    auto current(mCurrent++);
    
    return Rectangle((current % 2) * (mTitleWidth + mMarginX),
                     (current / 2) * (mHeight + mMarginY),
                     (current % 2) ? (mWidth - (mTitleWidth + mMarginX)) : mTitleWidth,
                     mHeight);
}
