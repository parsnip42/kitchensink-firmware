#ifndef INCLUDED_WIDGET_H
#define INCLUDED_WIDGET_H

#include "event/eventstage.h"
#include "ui/rasterline.h"
#include "ui/rectangle.h"

class Dimension;
class WidgetContainer;

class Widget : public EventStage
{
public:
    Widget() = default;
    virtual ~Widget() = default;
    
public:
    virtual void processEvent(const Event&) override;
    virtual void setFocused(bool focused);
    virtual void render(const RasterLine& rasterLine, int row) = 0;
    virtual void parented();
    virtual Dimension minimumSize() const;
    
public:
    void setParent(WidgetContainer* parent,
                   const Rectangle& parentRegion);

public:
    void invalidateWidget();
    
protected:
    Dimension widgetSize() const;
    void invalidateRegion(const Rectangle& region);

private:
    WidgetContainer* mParent;
    Rectangle        mParentRegion;
};


inline
void Widget::processEvent(const Event&)
{ }

inline
void Widget::setFocused(bool)
{ }

inline
void Widget::parented()
{ }

inline
Dimension Widget::minimumSize() const
{
    return Dimension(0, 0);
}

inline
Dimension Widget::widgetSize() const
{
    return Dimension(mParentRegion.width,
                     mParentRegion.height);
}

#endif
