#ifndef INCLUDED_LISTWIDGET_H
#define INCLUDED_LISTWIDGET_H

#include "types/range.h"
#include "ui/dimension.h"
#include "ui/rectangle.h"
#include "ui/surface.h"
#include "ui/widget.h"
#include "ui/widgetcontainer.h"

#include <cstdint>

class KeyEvent;
class Widget;

class ListWidget : public Widget
                 , public WidgetContainer
{
public:
    typedef Widget** iterator;
    
public:
    ListWidget(iterator itemsBegin,
               iterator itemsEnd,
               int      itemHeight);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;
    virtual void regionInvalidated(const Rectangle& region) override;

public:
    bool lastWidgetFocused() const;
    
private:
    Range<iterator> mItems;
    Dimension       mSize;
    int             mItemHeight;
    std::size_t     mItemCount;
    iterator        mFocused;
};

#endif





