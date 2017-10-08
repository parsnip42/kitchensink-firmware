#include "ui/surface.h"
#include "ui/widget.h"
#include "hardware/display.h"

#include "types/strref.h"

Surface::WidgetGuard::WidgetGuard(Surface& surface,
                                  Widget&  widget)
    : mSurface(surface)
    , mWidget(surface.rootWidget())
{
    mSurface.setRootWidget(&widget);
    mSurface.redraw();
}

Surface::WidgetGuard::~WidgetGuard()
{
    mSurface.setRootWidget(mWidget);
    
    if (mWidget)
    {
        mSurface.redraw();
    }
}


Surface::Surface(Display& display)
    : mDisplay(display)
    , mRootWidget(0)
{ }

void Surface::regionInvalidated(const Rectangle& region)
{
    if (mRootWidget)
    {
        for (auto y(region.y); y < (region.y + region.height); ++y)
        {
            RasterLine rasterLine(mDisplay.rasterLine());
            
            mRootWidget->render(rasterLine, y);

            mDisplay.rasterize(y);
        }
    }
}

void Surface::redraw()
{
    if (mRootWidget)
    {
        regionInvalidated(Rectangle(0,
                                    0,
                                    mDisplay.width(),
                                    mDisplay.height()));
    }
    else
    {
        clear();
    }
}

Widget* Surface::rootWidget()
{
    return mRootWidget;
}

void Surface::setRootWidget(Widget* rootWidget)
{
    mRootWidget = rootWidget;

    if (mRootWidget)
    {
        mRootWidget->setParent(this,
                               Rectangle(0,
                                         0,
                                         mDisplay.width(),
                                         mDisplay.height()));
    }
}

void Surface::clear()
{
    mDisplay.clear();
}

