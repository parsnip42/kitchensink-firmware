#include "ui/hstackwidget.h"

#include "ui/keys.h"
#include "keyevent.h"

#include <algorithm>

void HStackWidget::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);
    
    if (Keys::down(keyId) || Keys::ok(keyId))
    {
        if (event.pressed)
        {
            if (mFocused != mItems.end())
            {
                auto next(mFocused);
                
                ++next;
                
                if (next != mItems.end())
                {
                   mFocused->widget.setFocused(false);
                   mFocused->widget.invalidateWidget();
                    ++mFocused;
                   mFocused->widget.setFocused(true);
                   mFocused->widget.invalidateWidget();
                }
            }
        }
    }
    else if (Keys::up(keyId))
    {
        if (event.pressed)
        {
            if (mFocused != mItems.begin())
            {
               mFocused->widget.setFocused(false);
               mFocused->widget.invalidateWidget();
                --mFocused;
               mFocused->widget.setFocused(true);
               mFocused->widget.invalidateWidget();
            }
        }
    }
    else
    {
        if (mFocused != mItems.end())
        {
            mFocused->widget.processKeyEvent(event);
        }
    }
}

void HStackWidget::setFocused(bool focused)
{
    for (auto it(mItems.begin()); it != mItems.end(); ++it)
    {
        it->widget.setFocused(it == mFocused && focused);
    }
}

void HStackWidget::parented()
{
    auto size(widgetSize());
    int yOffset(0);
    int minimumItemHeight(0);

    // With a linear layout, all items are equally spaced, so we find the
    // maximum value of the minimum height of all items in a widget.
    if (mLinear)
    {
        for (auto& item : mItems)
        {
            minimumItemHeight = std::max(item.widget.minimumSize().height,
                                     minimumItemHeight);
        }
    }

    // And then parent with the standard margin of 1.
    for (auto& item : mItems)
    {
        auto& widget(item.widget);
        
        auto height(minimumItemHeight);

        if (!mLinear)
        {
            height = widget.minimumSize().height;
        }
        
        widget.setParent(this,
                         Rectangle(0,
                                   yOffset,
                                   size.width,
                                   height));
        
        yOffset += height + 1;
        item.yOffset = yOffset;
    }
}

void HStackWidget::render(const RasterLine& rasterLine, int row)
{
    auto rowOffset(0);
    
    for (auto& item : mItems)
    {
        if (row < item.yOffset)
        {
            if (row < item.yOffset - 1)
            {
                item.widget.render(rasterLine, row - rowOffset);
            }
            
            return;
        }

        rowOffset = item.yOffset;
    }
}

void HStackWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

bool HStackWidget::lastWidgetFocused() const
{
    if (mFocused != mItems.end())
    {
        auto next(mFocused);
        
        ++next;
        
        if (next != mItems.end())
        {
            return false;
        }
    }
    
    return true;
}
