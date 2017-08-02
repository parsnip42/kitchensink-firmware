#ifndef INCLUDED_WIDGET_H
#define INCLUDED_WIDGET_H

#include "keyeventstage.h"
#include "ui/rasterline.h"
#include "ui/rectangle.h"

class Dimension;
class WidgetContainer;

class Widget : public KeyEventStage
{
public:
    Widget() = default;
    virtual ~Widget() = default;
    
public:
    virtual void processKeyEvent(const KeyEvent&) override;
    virtual void setFocused(bool focused);
    virtual void render(const RasterLine& rasterLine, int row) = 0;
    virtual void parented();
    
public:
    void setParent(WidgetContainer* parent,
                   const Rectangle& parentRegion);

protected:
    Dimension getSize() const;
    void invalidateWidget();
    void invalidateRegion(const Rectangle& region);

private:
    WidgetContainer* mParent;
    Rectangle        mParentRegion;
};


inline
void Widget::processKeyEvent(const KeyEvent&)
{ }

inline
void Widget::setFocused(bool)
{ }

inline
void Widget::parented()
{ }

inline
Dimension Widget::getSize() const
{
    return Dimension(mParentRegion.width,
                     mParentRegion.height);
}

#endif
