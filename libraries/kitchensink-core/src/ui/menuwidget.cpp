#include "ui/menuwidget.h"

#include "ui/font.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"
#include "event/event.h"


MenuWidget::MenuWidget(const DataSource& dataSource)
    : filterIndex(dataSource.size())
    , mDataSource(dataSource)
    , mSelectedIndex(0)
    , mFocused(true)
    , mWidgetIndex(0xffff)
{
}

bool MenuWidget::processEvent(const Event& event)
{
    if (Keys::ok(event))
    {
        itemSelected.fireAction();
        
        return true;
    }
    else if (Keys::pageUp(event))
    {
        moveSelection(-5);
    }
    else if (Keys::pageDown(event))
    {
        moveSelection(5);
    }
    else if (Keys::prev(event))
    {
        moveSelection(-1);
    }
    else if (Keys::next(event))
    {
        moveSelection(1);
    }
    else if (Keys::backspace(event))
    {
        if (!filterStr.empty())
        {
            filterStr.erase(filterStr.end() - 1);
            applyFilter();
            update();
        }
    }
    else
    {
        mVKeyboard.processEvent(event);

        auto newChar(mVKeyboard.consumeChar());
        
        if (newChar)
        {
            if (filterStr.length() < filterStr.capacity())
            {
                filterStr.insert(filterStr.end(), newChar);
                
                // Optimistic check for results - apply the filter first and then
                // revert the change only if no results are found.
                applyFilter();
                
                if (filterIndex.filteredSize() == 0)
                {
                    filterStr.erase(filterStr.end() - 1);
                    applyFilter();
                }
                else
                {
                    update();
                }
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

void MenuWidget::setFocused(bool focused)
{
    mFocused = focused;
    invalidateWidget();
}

void MenuWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(widgetSize());
    
    int itemCount(filterIndex.filteredSize());
    
    // Selected item * font height is the y position of the selected item
    // relative to the top of the menu. By itself, this keeps the selected item
    // at the top of the rendered area.
    int offset(mSelectedIndex * MenuItemWidget::kPreferredHeight);

    // This is the height of the rendered portion of the menu.
    int menuHeight(std::min(size.height, itemCount * MenuItemWidget::kPreferredHeight));

    // Subtracting the font height from the rendered height of the menu gives us
    // the maximum possible offset - this is where the selected menu item will
    // appear at the very bottom of the rendered area.
    int offsetMax(menuHeight - Font::kHeight);

    // And now we subtract by a range of 0 to offsetMax inclusive based on the
    // currently-selected menu item.
    offset -= ((mSelectedIndex * offsetMax) / (itemCount - 1));


    row += offset;
    
    int index(row / MenuItemWidget::kPreferredHeight);

    if (index < itemCount)
    {
        populateMenuItem(index);
        mWidget.render(rasterLine, row % MenuItemWidget::kPreferredHeight);
    }
}

void MenuWidget::regionInvalidated(const Rectangle& region)
{
    // This space intentionally left blank - we manage any invalidation within
    // this widget and not it's children.
}

void MenuWidget::moveSelection(int direction)
{
    mSelectedIndex += direction;

    // Clamp to data source size.
    mSelectedIndex = std::max(0, mSelectedIndex);
    mSelectedIndex = std::min<int>(filterIndex.filteredSize() - 1, mSelectedIndex);

    invalidateWidget();
}

void MenuWidget::populateMenuItem(int index)
{
    if (index != mWidgetIndex)
    {
        const auto& item(mDataSource[filterIndex[index]]);

        mWidget.text     = item.title;
        mWidget.shortcut = item.shortcut;
        mWidget.filter   = filterStr;
        
        mWidget.setParent(this, Rectangle(0, 0, widgetSize().width, MenuItemWidget::kPreferredHeight));
        mWidget.setFocused(mFocused && index == mSelectedIndex);
    }

    mWidgetIndex = index;
}

MenuWidget::Item MenuWidget::selectedItem() const
{
    return mDataSource[filterIndex[mSelectedIndex]];
}

void MenuWidget::applyFilter()
{
    bool fireShortcut(false);
    
    filterIndex.filter(
        mDataSource.size(),
        [&](std::size_t index)
        {
            const auto& item(mDataSource[index]);

            // Typing a shortcut instantly activates the item, however defer
            // this until we've finished processing and default to the first
            // match.
            if (!filterStr.empty() &&
                item.shortcut == filterStr &&
                !fireShortcut)
            {
                mSelectedIndex = index;
                fireShortcut = true;
            }
            
            return (StrRef(item.title).beginsWithCase(filterStr) ||
                    StrRef(item.shortcut).beginsWithCase(filterStr));
        });

    if (fireShortcut)
    {
        itemSelected.fireAction();
    }
}

void MenuWidget::update()
{
    mWidgetIndex = 0xffff;
    moveSelection(0);
}
