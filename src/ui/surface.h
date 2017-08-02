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
public:
    static constexpr int     kHeight     = 64;
    static constexpr int     kWidth      = 240;
    static constexpr int     kFontWidth  = Font::kWidth;
    static constexpr int     kFontHeight = Font::kHeight;
    static constexpr uint8_t kScrollMax  = 128;
    
public:
    typedef UI4Array<kWidth> RowBuf;
    
public:
    explicit Surface(Display& display);

public:
    virtual void regionInvalidated(const Rectangle& region) override;

    void redraw();
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

#endif
