#ifndef INCLUDED_LISTLAYOUT_H
#define INCLUDED_LISTLAYOUT_H

#include "ui/dimension.h"
#include "ui/surface.h"
#include "ui/keys.h"
#include "keyevent.h"

#include <array>
#include <cstdint>
#include <initializer_list>

class KeyEvent;
class Widget;

template <std::size_t Size>
class ListLayout
{
public:
    typedef std::array<Widget*, Size> Items;
    
public:
    ListLayout(int     width,
               int     height,
               int     itemHeight,
               int     marginY,
               Items&& items);

public:
    void processKeyEvent(const KeyEvent& event);
    void render(Surface::RowData& rowData, int row);

private:
    int         mWidth;
    int         mHeight;
    int         mItemHeight;
    int         mMarginY;
    Items       mItems;
    std::size_t mFocus;
};

template <std::size_t Size>
inline
ListLayout<Size>::ListLayout(int     width,
                             int     height,
                             int     itemHeight,
                             int     marginY,
                             Items&& items)
    : mWidth(width)
    , mHeight(height)
    , mItemHeight(itemHeight)
    , mMarginY(marginY)
    , mItems(std::move(items))
    , mFocus(0)
{
    for (auto* item : mItems)
    {
        item->setSize(Dimension(width, itemHeight));
    }

    mItems[mFocus]->setFocused(true);
}

template <std::size_t Size>
inline
void ListLayout<Size>::render(Surface::RowData& rowData, int row)
{
    auto totalItemHeight(mItemHeight + mMarginY);
    std::size_t index(row / totalItemHeight);
    
    if (index >= 0 && index < mItems.size())
    {
        auto itemRow(row % totalItemHeight);

        if (itemRow < mItemHeight)
        {
            mItems[index]->render(rowData, itemRow);
        }
    }
}

template <std::size_t Size>
inline
void ListLayout<Size>::processKeyEvent(const KeyEvent& event)
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

#endif





