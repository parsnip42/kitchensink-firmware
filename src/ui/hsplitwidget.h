#ifndef INCLUDED_HSPLITWIDGET_H
#define INCLUDED_HSPLITWIDGET_H

#include "widget.h"
#include "widgetcontainer.h"

class HSplitWidget : public Widget
                   , public WidgetContainer
{
public:
    HSplitWidget(Widget& nTop,
                 Widget& nBottom,
                 int     nSplitOffset);

public:
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void regionInvalidated(const Rectangle& region) override;
    virtual void parented() override;

public:
    Widget& top;
    Widget& bottom;
    int     splitOffset;
};

#endif
