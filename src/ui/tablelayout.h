#ifndef INCLUDED_TABLELAYOUT_H
#define INCLUDED_TABLELAYOUT_H

#include "rectangle.h"

namespace UI
{

class TableLayout
{
public:
    TableLayout(int titleWidth,
                int width,
                int height,
                int margin);

public:
    Rectangle next();
    
private:
    int mCurrent;
    int mTitleWidth;
    int mWidth;
    int mHeight;
    int mMargin;
};

}

#endif /* INCLUDED_TABLELAYOUT_H */
