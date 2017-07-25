#include "ui/menu.h"
#include "ui/keys.h"
#include "data/keycodes.h"
#include "data/keymap.h"

#include <cstdint>
#include <algorithm>

namespace UI
{

void Menu::poll()
{
    mSurface.clear();
    redraw();
    
    while (!mQuit)
    {
        mPipeline.poll([&](const KeyEvent& event,
                           KeyEventStage&  next)
                       {
                           processKeyEvent(event, next);
                       });
    }
    
    mSurface.clear();
}

void Menu::processKeyEvent(const KeyEvent& event,
                           KeyEventStage&  next)
{
    mVKeyboard.processKeyEvent(event);
        
    auto state(mVKeyboard.readState());
    auto keyId(state.activeKey);
        
    if (Keys::pageUp(keyId))
    {
        moveSelection(-5);
    }
    else if (Keys::pageDown(keyId))
    {
        moveSelection(5);
    }
    else if (Keys::up(keyId))
    {
        moveSelection(-1);
    }
    else if (Keys::down(keyId))
    {
        moveSelection(1);
    }
    else if (Keys::ok(keyId))
    {
        Item item;

        filteredItem(item, mSelected);
            
        next.processKeyEvent(KeyEvent(item.keyId, true));
        next.processKeyEvent(KeyEvent(item.keyId, false));
        mQuit = true;
    }
    else if (Keys::cancel(keyId))
    {
        mQuit = true;
    }
    else if (keyId.type() == KeyId::Type::kKey)
    {
        if (keyId.value() == KeyCodes::Backspace)
        {
            mFilter.erase(mFilter.end() - 1);
            moveSelection(0);
        }
        else
        {
            char newChar(state.activeChar);

            if (newChar)
            {
                mFilter.insert(mFilter.end(), newChar);

                if (processExactFilterMatch())
                {
                    mQuit = true;
                }
                    
                moveSelection(0);
            }
        }
    }
}


void Menu::moveSelection(int selectionOffset)
{
    auto itemCount(filteredItemCount());
    
    if (static_cast<int>(mSelected) < -selectionOffset)
    {
        mSelected = 0;
    }
    else if ((mSelected + selectionOffset) > (itemCount - 1))
    {
        mSelected = itemCount -1;
    }
    else
    {
        mSelected += selectionOffset;
    }

    redraw();
}

void Menu::redraw()
{
    if (mFilter.empty())
    {
        paintMenu(0, Surface::kHeight);
    }
    else
    {
        mSurface.paintTextC(0, 0, Surface::kWidth, mFilter, 0x7);
        paintMenu(Surface::kFontHeight, Surface::kHeight - Surface::kFontHeight);
    }
}

void Menu::paintMenu(int start,
                     int height)
{    
    static const Surface::ColorMap colorMap(0xf, 0x0);
    static const Surface::ColorMap invColorMap(0x0, 0xf);

    auto itemCount(filteredItemCount());

    // Selected item * font height is the y position of the selected item
    // relative to the top of the menu. By itself, this keeps the selected item
    // at the top of the rendered area.
    int offset(mSelected * Surface::kFontHeight);

    // This is the height of the rendered portion of the menu.
    int menuHeight(std::min<int>(height, itemCount * Surface::kFontHeight));

    // Subtracting the font height from the rendered height of the menu gives us
    // the maximum possible offset - this is where the selected menu item will
    // appear at the very bottom of the rendered area.
    int offsetMax(menuHeight - Surface::kFontHeight);

    // And now we subtract by a range of 0 to offsetMax inclusive based on the
    // currently-selected menu item.
    offset -= ((mSelected * offsetMax) / (itemCount - 1));

    mSurface.initRegion(0, start, Surface::kWidth, height);

    int y(0);

    while (y < height)
    {
        int menuPosition(y + offset);
        std::size_t menuItem(menuPosition / Surface::kFontHeight);
        int menuItemOffset(menuPosition % Surface::kFontHeight);

        StrBuf<48> text;
        KeyId keyId;

        // FIXME: This should really iterate rather than performing a linear
        // search across the entire list from the start.
        Item item;
        
        filteredItem(item, menuItem);
        
        const auto& colors(menuItem != mSelected ? colorMap : invColorMap);

        // Paint the menu item line by line until we hit the font height or the
        // bottom of the rendered region, whichever comes first.
        while (y < height && menuItemOffset < Surface::kFontHeight)
        {
            mSurface.paintTextLineC(item.title, Surface::kWidth, menuItemOffset, colors);

            ++menuItemOffset;
            ++y;
        }
    }
}

bool Menu::matchesFilter(const Menu::Item& item)
{
    return StrRef(item.title).beginsWithCase(mFilter) ||
        StrRef(item.shortcut).beginsWithCase(mFilter);
}

void Menu::filteredItem(Menu::Item& item,
                        std::size_t index)
{
    std::size_t count(0);

    for (std::size_t i(0); i < mDataSource.getItemCount(); ++i)
    {
        mDataSource.getItem(item, i);

        if (matchesFilter(item) && (count++ >= index))
        {
            return;
        }
    }

    // Return blank when out of range.
    item = Menu::Item();
}

std::size_t Menu::filteredItemCount()
{
    std::size_t count(0);

    for (std::size_t i(0); i < mDataSource.getItemCount(); ++i)
    {
        StrBuf<20> text;
        KeyId keyId;
        
        Item item;
        
        mDataSource.getItem(item, i);

        if (matchesFilter(item))
        {
            ++count;
        }
    }

    return count;
}

bool Menu::processExactFilterMatch()
{
    for (std::size_t i(0); i < mDataSource.getItemCount(); ++i)
    {
        Item item;

        mDataSource.getItem(item, i);
        
        if (StrRef(item.shortcut).equalsCase(mFilter))
        {
            // mNext.processKeyEvent(KeyEvent(item.keyId, true));
            // mNext.processKeyEvent(KeyEvent(item.keyId, False));
            return true;
        }
    }

    return false;
}

}
