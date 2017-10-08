#ifndef INCLUDED_UI_SURFACE_H
#define INCLUDED_UI_SURFACE_H

#include "ui/dimension.h"
#include "ui/font.h"
#include "ui/widgetcontainer.h"
#include "ui/rasterline.h"
#include "types/range.h"

#include <array>
#include <cstdint>

class Display;
class Widget;

class Surface : public WidgetContainer
{
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
    void clear();

private:
    Display& mDisplay;
    Widget*  mRootWidget;
    
private:
    Surface(const Surface&) = delete;
    Surface& operator=(const Surface&) = delete;
};

#endif
