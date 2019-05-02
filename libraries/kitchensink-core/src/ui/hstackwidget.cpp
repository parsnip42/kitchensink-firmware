#include "ui/hstackwidget.h"

#include "ui/keys.h"
#include "event/event.h"

#include <algorithm>


bool HStackWidget::processEvent(const Event& event)
{
    if (mFocused != mItems.end() &&
        mFocused->widget->processEvent(event))
    {
        return true;
    }
    else if (Keys::next(event) || Keys::okReleased(event))
    {
        if (!focusNext() && Keys::okReleased(event))
        {
            return applied.fireAction();
        }
        
        // return true;
    }
    else if (Keys::prev(event))
    {
        focusPrev();

        return true;
    }
    
    return false;
}

void HStackWidget::setFocused(bool focused)
{
    for (auto it(mItems.begin()); it != mItems.end(); ++it)
    {
        it->widget->setFocused(it == mFocused && focused);
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
            minimumItemHeight = std::max(item.widget->minimumSize().height,
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
            height = widget->minimumSize().height;
        }
        
        widget->setParent(this,
                         Rectangle(0,
                                   yOffset,
                                   size.width,
                                   height));
        
        item.yOffset = yOffset;
        item.height  = height;
        
        yOffset += height;
    }
    
    mContentHeight = yOffset;

    setFocused(mFocused);
}

void HStackWidget::render(const RasterLine& rasterLine, int row)
{
    row += renderOffset();

    // TODO: Binary search for target widget.
    for (auto& item : mItems)
    {
        if (row < (item.yOffset + item.height))
        {
            item.widget->render(rasterLine, row - item.yOffset);
            return;
        }
    }
}

void HStackWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region.offsetY(-renderOffset()));
}

Widget& HStackWidget::focused() const
{
    return *mFocused->widget;
}

void HStackWidget::setFocused(const Widget& widget)
{
    for (auto it(mItems.begin()); it != mItems.end(); ++it)
    {
        if (it->widget == &widget)
        {
            it->widget->setFocused(true);
            mFocused = it;
        }
        else
        {
            it->widget->setFocused(false);
        }
    }
}

bool HStackWidget::focusPrev()
{
    auto next(mFocused);
    
    while (next != mItems.begin())
    {
        --next;
            
        if (next->widget->canFocus())
        {
            switchFocus(next);

            return true;
        }
    }

    return false;
}

bool HStackWidget::focusNext()
{
    auto end(mItems.end());

    --end;
    
    auto next(mFocused);

    while (next != end)
    {
        ++next;
        
        if (next->widget->canFocus())
        {
            switchFocus(next);
            
            return true;
        }
    }

    return false;
}

void HStackWidget::switchFocus(HStackWidget::iterator next)
{
    mFocused->widget->setFocused(false);
    mFocused = next;
    mFocused->widget->setFocused(true);

    // We could optimise this down to just the affected child widgets if the
    // focus change doesn't make this widget scroll.
    invalidateWidget();
}

int HStackWidget::renderOffset() const
{
    auto size(widgetSize());

    auto offsetMax(std::max(size.height, mContentHeight) - size.height);
    
    return ((offsetMax * std::distance(mItems.begin(), mFocused)) / (std::distance(mItems.begin(), mItems.end()) - 1));
}
