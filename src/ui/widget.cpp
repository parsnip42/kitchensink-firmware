#include "ui/widget.h"

#include "ui/widgetcontainer.h"

void Widget::setParent(WidgetContainer* parent,
                       const Rectangle& parentRegion)
{
    mParent       = parent;
    mParentRegion = parentRegion;

    parented();
}

void Widget::invalidateWidget()
{
    mParent->regionInvalidated(Rectangle(mParentRegion));
}

void Widget::invalidateRegion(const Rectangle& region)
{
    // TODO: clip
    
    mParent->regionInvalidated(Rectangle(mParentRegion.x + region.x,
                                              mParentRegion.y + region.y,
                                              region.width,
                                              region.height));
}
