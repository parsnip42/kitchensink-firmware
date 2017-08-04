#include "ui/hsplitwidget.h"

HSplitWidget::HSplitWidget(Widget& top,
                           Widget& bottom,
                           int     splitOffset)
    : mTop(top)
    , mBottom(bottom)    
    , mSplitOffset(splitOffset)
{ }

void HSplitWidget::render(const RasterLine& rasterLine, int row)
{
    if (row < mSplitOffset)
    {
        mTop.render(rasterLine, row);
    }
    else
    {
        mBottom.render(rasterLine, row - mSplitOffset);
    }   
}

void HSplitWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

void HSplitWidget::parented()
{
    auto size(widgetSize());
    
    mTop.setParent(this,
                   Rectangle(0,
                             0,
                             size.width,
                             mSplitOffset));
    mBottom.setParent(this,
                      Rectangle(0,
                                mSplitOffset,
                                size.width,
                                size.height - mSplitOffset));
}


