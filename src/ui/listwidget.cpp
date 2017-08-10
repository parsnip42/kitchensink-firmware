#include "ui/listwidget.h"

#include "ui/keys.h"
#include "keyevent.h"

ListWidget::ListWidget(iterator itemsBegin,
                       iterator itemsEnd,
                       int      itemHeight)
    : mItems(itemsBegin, itemsEnd)
    , mItemHeight(itemHeight)
    , mItemCount(std::distance(itemsBegin, itemsEnd))
    , mFocused(itemsBegin)
{ }

void ListWidget::processKeyEvent(const KeyEvent& event)
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
                    (*mFocused)->setFocused(false);
                    (*mFocused)->invalidateWidget();
                    ++mFocused;
                    (*mFocused)->setFocused(true);
                    (*mFocused)->invalidateWidget();
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
                (*mFocused)->setFocused(false);
                (*mFocused)->invalidateWidget();
                --mFocused;
                (*mFocused)->setFocused(true);
                (*mFocused)->invalidateWidget();
            }
        }
    }
    else
    {
        if (mFocused != mItems.end())
        {
            (*mFocused)->processKeyEvent(event);
        }
    }
}

void ListWidget::setFocused(bool focused)
{
    if (mFocused != mItems.end())
    {
        auto* widget(*mFocused);
        
        widget->setFocused(focused);
        widget->invalidateWidget();
    }
}

void ListWidget::parented()
{
    auto size(widgetSize());
    auto totalItemHeight(mItemHeight + 1);

    int index(0);
    
    for (auto item : mItems)
    {
        item->setParent(this,
                        Rectangle(0,
                                  totalItemHeight * index++,
                                  size.width,
                                  mItemHeight));
    }
    
    if (mFocused != mItems.end())
    {
        (*mFocused)->setFocused(true);
    }
}

void ListWidget::render(const RasterLine& rasterLine, int row)
{
    auto totalItemHeight(mItemHeight + 1);
    std::size_t index(row / totalItemHeight);
    
    if (index < mItemCount)
    {
        auto itemRow(row % totalItemHeight);

        if (itemRow < mItemHeight)
        {
            (*(mItems.begin() + index))->render(rasterLine, itemRow);
        }
    }
}

void ListWidget::regionInvalidated(const Rectangle& region)
{
    invalidateRegion(region);
}

bool ListWidget::lastWidgetFocused() const
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
