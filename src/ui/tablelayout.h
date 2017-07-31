#ifndef INCLUDED_TABLELAYOUT_H
#define INCLUDED_TABLELAYOUT_H

#include "rectangle.h"

class TableLayout
{
public:
    TableLayout(int titleWidth,
                int width,
                int height,
                int marginX,
                int marginY);

public:
    Rectangle next();
    
private:
    int mCurrent;
    int mTitleWidth;
    int mWidth;
    int mHeight;
    int mMarginX;
    int mMarginY;
};

#endif
