#include "ui/menuwidget.h"

#include "ui/font.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"
#include "keyevent.h"

MenuWidget::MenuWidget(const DataSource& dataSource)
    : filterIndex(dataSource.size())
    , mDataSource(dataSource)
    , mSelectedIndex(0)
    , mFocused(true)
    , mWidgetIndex(0xffff)
{
}

void MenuWidget::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (event.pressed)
    {
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
    }
}

void MenuWidget::setFocused(bool focused)
{
    mFocused = focused;
    invalidateWidget();
}

void MenuWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(getSize());
    
    int itemCount(filterIndex.filteredSize());
    
    // Selected item * font height is the y position of the selected item
    // relative to the top of the menu. By itself, this keeps the selected item
    // at the top of the rendered area.
    int offset(mSelectedIndex * MenuItemWidget::kHeight);

    // This is the height of the rendered portion of the menu.
    int menuHeight(std::min(size.height, itemCount * MenuItemWidget::kHeight));

    // Subtracting the font height from the rendered height of the menu gives us
    // the maximum possible offset - this is where the selected menu item will
    // appear at the very bottom of the rendered area.
    int offsetMax(menuHeight - Font::kHeight);

    // And now we subtract by a range of 0 to offsetMax inclusive based on the
    // currently-selected menu item.
    offset -= ((mSelectedIndex * offsetMax) / (itemCount - 1));


    row += offset;
    
    int index(row / MenuItemWidget::kHeight);

    if (index < itemCount)
    {
        populateMenuItem(index);
        mWidget.render(rasterLine, row % MenuItemWidget::kHeight);
    }
}

void MenuWidget::regionInvalidated(const Rectangle& region)
{
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
        mWidget = mDataSource[filterIndex[index]];
        mWidget.setParent(this, Rectangle(0, 0, getSize().width, MenuItemWidget::kHeight));
        mWidget.setFocused(mFocused && index == mSelectedIndex);
    }

    mWidgetIndex = index;
}

int MenuWidget::selectedIndex() const
{
    return mSelectedIndex;
}

void MenuWidget::update()
{
    moveSelection(0);
}
