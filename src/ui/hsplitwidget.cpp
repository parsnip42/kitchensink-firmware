#include "ui/hsplitwidget.h"

HSplitWidget::HSplitWidget(Widget& nTop,
                           Widget& nBottom,
                           int     nSplitOffset)
    : top(nTop)
    , bottom(nBottom)    
    , splitOffset(nSplitOffset)
{ }

void HSplitWidget::render(const RasterLine& rasterLine, int row)
{
    if (row < splitOffset)
    {
        top.render(rasterLine, row);
    }
    else
    {
        bottom.render(rasterLine, row - splitOffset);
    }   
}

void HSplitWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

void HSplitWidget::parented()
{
    auto size(widgetSize());
    
    top.setParent(this,
                  Rectangle(0,
                            0,
                            size.width,
                            splitOffset));
    bottom.setParent(this,
                     Rectangle(0,
                               splitOffset,
                               size.width,
                               size.height - splitOffset));
}
