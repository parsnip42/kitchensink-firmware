#ifndef INCLUDED_LISTWIDGET_H
#define INCLUDED_LISTWIDGET_H

#include "ui/dimension.h"
#include "ui/surface.h"
#include "ui/keys.h"
#include "ui/widget.h"
#include "ui/widgetcontainer.h"
#include "dimension.h"
#include "keyevent.h"
#include "rectangle.h"

#include <array>
#include <cstdint>
#include <initializer_list>

class KeyEvent;
class Widget;

template <std::size_t Size>
class ListWidget : public Widget
                 , public WidgetContainer
{
public:
    typedef std::array<Widget*, Size> Items;
    
public:
    ListWidget(int     itemHeight,
               int     marginY,
               Items&& items);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;
    virtual void regionInvalidated(const Rectangle& region) override;
    
private:
    Dimension   mSize;
    int         mItemHeight;
    int         mMarginY;
    Items       mItems;
    std::size_t mFocus;
};


template <std::size_t Size>
inline
ListWidget<Size>::ListWidget(int     itemHeight,
                             int     marginY,
                             Items&& items)
    : mItemHeight(itemHeight)
    , mMarginY(marginY)
    , mItems(std::move(items))
    , mFocus(0)
{ }

template <std::size_t Size>
inline
void ListWidget<Size>::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);
    
    if (Keys::down(keyId) || Keys::ok(keyId))
    {
        if (event.pressed)
        {
            if (mFocus < mItems.size() - 1)
            {
                mItems[mFocus]->setFocused(false);
                ++mFocus;
                mItems[mFocus]->setFocused(true);
            }
        }
    }
    else if (Keys::up(keyId))
    {
        if (event.pressed)
        {
            if (mFocus > 0)
            {
                mItems[mFocus]->setFocused(false);
                --mFocus;
                mItems[mFocus]->setFocused(true);
            }
        }
    }
    else
    {
        mItems[mFocus]->processKeyEvent(event);
    }
}

template <std::size_t Size>
inline
void ListWidget<Size>::setFocused(bool focused)
{
    mItems[mFocus]->setFocused(true);
}

template <std::size_t Size>
inline
void ListWidget<Size>::parented()
{
    auto size(widgetSize());
    auto totalItemHeight(mItemHeight + mMarginY);

    int index(0);
    
    for (auto* item : mItems)
    {
        item->setParent(this,
                        Rectangle(0,
                                  totalItemHeight * index++,
                                  size.width,
                                  mItemHeight));
    }

    mItems[mFocus]->setFocused(true);
}

template <std::size_t Size>
inline
void ListWidget<Size>::render(const RasterLine& rasterLine, int row)
{
    auto totalItemHeight(mItemHeight + mMarginY);
    std::size_t index(row / totalItemHeight);
    
    if (index >= 0 && index < mItems.size())
    {
        auto itemRow(row % totalItemHeight);

        if (itemRow < mItemHeight)
        {
            mItems[index]->render(rasterLine, itemRow);
        }
    }
}

template <std::size_t Size>
inline
void ListWidget<Size>::regionInvalidated(const Rectangle& region)
{
    Rectangle r(region.x,
                region.y,
                region.width,
                region.height);
    
    invalidateRegion(r);
}

#endif





