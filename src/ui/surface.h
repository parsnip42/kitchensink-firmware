#ifndef INCLUDED_UI_SURFACE_H
#define INCLUDED_UI_SURFACE_H

#include "ui/dimension.h"
#include "ui/font.h"
#include "ui/widgetcontainer.h"
#include "types/ui4array.h"
#include "types/range.h"
#include "types/arrayref.h"

#include <array>
#include <cstdint>

class Display;
class Widget;

class Surface : public WidgetContainer
{
private:
    static constexpr int kWidth  = 240;
    static constexpr int kHeight = 64;
    
public:
    typedef UI4Array<kWidth> RowBuf;

public:
    class WidgetGuard
    {
    public:
        WidgetGuard(Surface& surface,
                    Widget&  widget);

        ~WidgetGuard();

    private:
        Surface& mSurface;
        Widget*  mWidget;

    private:
        WidgetGuard(const WidgetGuard&) = delete;
        WidgetGuard& operator=(const WidgetGuard&) = delete;
    };
    
public:
    explicit Surface(Display& display);

public:
    virtual void regionInvalidated(const Rectangle& region) override;

    void redraw();
    Widget* rootWidget();
    void setRootWidget(Widget* rootWidget);

public:
    void initRegion(int x, int y, int w, int h);
    void render(const RowBuf& row, int y);
    void clear();

private:
    Display& mDisplay;
    Widget*  mRootWidget;
    
private:
    Surface(const Surface&) = delete;
    Surface& operator=(const Surface&) = delete;
};


inline
Surface::WidgetGuard::WidgetGuard(Surface& surface,
                                  Widget&  widget)
    : mSurface(surface)
    , mWidget(surface.rootWidget())
{
    mSurface.setRootWidget(&widget);
    mSurface.redraw();
}

inline
Surface::WidgetGuard::~WidgetGuard()
{
    mSurface.setRootWidget(mWidget);
    mSurface.redraw();
}

#endif
