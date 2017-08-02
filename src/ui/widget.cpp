#include "ui/widget.h"

#include "ui/widgetcontainer.h"

void Widget::processKeyEvent(const KeyEvent&)
{ }

void Widget::setParent(WidgetContainer* parent,
                       const Rectangle& parentRegion)
{
    mParent       = parent;
    mParentRegion = parentRegion;

    parented();
}

void Widget::invalidateWidget()
{
    invalidateParentRegion(mParentRegion);
}

void Widget::invalidateParentRegion(const Rectangle& region)
{
    // TODO: clip
    
    mParent->invalidateRegion(Rectangle(mParentRegion.x + region.x,
                                        mParentRegion.y + region.y,
                                        region.width,
                                        region.height));
}
