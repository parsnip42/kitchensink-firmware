#include "ui/surface.h"
#include "ui/widget.h"
#include "display.h"

#include "types/strref.h"

Surface::Surface(Display& display)
    : mDisplay(display)
{ }

void Surface::regionInvalidated(const Rectangle& region)
{
    if (mRootWidget)
    {
        for (auto y(region.y); y < (region.y + region.height); ++y)
        {
            RowBuf row;
            RasterLine rasterLine(row);
            
            mRootWidget->render(rasterLine, y);
            render(row, y);
        }
    }
}

void Surface::redraw()
{
    regionInvalidated(Rectangle(0, 0, kWidth, kHeight));
}

void Surface::setRootWidget(Widget* rootWidget)
{
    mRootWidget = rootWidget;

    if (mRootWidget)
    {
        mRootWidget->setParent(this,
                               Rectangle(0, 0, kWidth, kHeight));
    }
}

void Surface::initRegion(int x, int y, int w, int h)
{
    mDisplay.initRegion(x, y, w, h);
}

void Surface::render(const RowBuf& row, int y)
{
    initRegion(0, y, kWidth, 1);

    for (auto data : row.rawData())
    {
        mDisplay.writeData(data);
    }
}

void Surface::clear()
{
    mDisplay.clear();
    mDisplay.scroll(0);
}

