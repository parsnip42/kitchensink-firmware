#ifndef INCLUDED_HSPLITWIDGET_H
#define INCLUDED_HSPLITWIDGET_H

#include "widget.h"
#include "widgetcontainer.h"

class HSplitWidget : public Widget
                   , public WidgetContainer
{
public:
    HSplitWidget(Widget& top,
                 Widget& bottom,
                 int     splitPct);

public:
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void invalidateParentRegion(const Rectangle& region) override;
    virtual void parented() override;

private:
    Widget& mTop;
    Widget& mBottom;    
    int     mSplitOffset;
};

#endif
