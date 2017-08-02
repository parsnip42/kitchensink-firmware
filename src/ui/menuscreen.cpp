#include "ui/menuscreen.h"

#include "autorepeat.h"
#include "eventmanager.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"

MenuScreen::MenuDataSource::MenuDataSource(const MenuScreen::DataSource& dataSource)
    : mDataSource(dataSource)
{ }

void MenuScreen::MenuDataSource::item(MenuItemWidget& widget,
                                      std::size_t     index) const
{
    Item item;

    mDataSource.item(item, index);
    
    widget.text = item.title;
}

std::size_t MenuScreen::MenuDataSource::size() const
{
    return mDataSource.size();
}


MenuScreen::MenuScreen(const StrRef&     title,
                       const DataSource& dataSource,
                       Surface&          surface,
                       EventManager&     eventManager)
    : mTitle(title)
    , mSurface(surface)
    , mEventManager(eventManager)
    , mMenuDataSource(dataSource)
    , mMenuLayout(mMenuDataSource)
    , mTitleWidget(title)
    , mHSplit(mTitleWidget, mMenuLayout, 12)
    , mQuit(false)
{
    mHSplit.setParent(this,
                      Rectangle(0,
                                0,
                                Surface::kWidth,
                                Surface::kHeight));
}

void MenuScreen::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);
    
    if (Keys::ok(keyId))
    {
        mQuit = true;
    }
    else if (Keys::cancel(keyId))
    {
        mQuit = true;
    }
    else
    {
        mMenuLayout.processKeyEvent(event);
    }
}

void MenuScreen::poll()
{
    redraw();
    
    AutoRepeat autoRepeat(mEventManager.timer,
                          *this);
    while (!mQuit)
    {
        mEventManager.poll(autoRepeat);
    }
}

void MenuScreen::invalidateParentRegion(const Rectangle& region)
{
    for (auto y(region.y); y < (region.y + region.height); ++y)
    {
        Surface::RowBuf row;
        RasterLine rasterLine(row);

        mHSplit.render(rasterLine, y);
        mSurface.render(row, y);
    }
}

void MenuScreen::redraw()
{
    invalidateParentRegion(Rectangle(0,
                                     0,
                                     Surface::kWidth,
                                     Surface::kHeight));
}
