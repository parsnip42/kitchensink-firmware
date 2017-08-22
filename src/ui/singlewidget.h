#ifndef INCLUDED_SINGLEWIDGET_H
#define INCLUDED_SINGLEWIDGET_H

#include "ui/widget.h"
#include "ui/widgetcontainer.h"

class SingleWidget : public Widget
                   , public WidgetContainer
{
public:
    explicit SingleWidget(Widget& widget);

public:
    virtual void processEvent(const Event& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;
    virtual void regionInvalidated(const Rectangle& region) override;

public:
    void setWidget(Widget& widget);
    
private:
    Widget* mWidget;
    bool    mParented;
};

#endif
