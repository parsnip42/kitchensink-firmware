#include "ui/menuscreen.h"

#include "autorepeat.h"
#include "eventmanager.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"

MenuScreen::MenuDataSource::MenuDataSource(const MenuScreen::DataSource& dataSource)
    : mDataSource(dataSource)
{ }

MenuItemWidget MenuScreen::MenuDataSource::operator[](std::size_t index) const
{
    MenuItemWidget widget;
    
    widget.text = mDataSource[index].title;

    return widget;
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
    , mDataSource(dataSource)
    , mMenuDataSource(dataSource)
    , mMenuWidget(mMenuDataSource)
    , mTitleWidget(title, eventManager)
    , mHSplit(mTitleWidget, mMenuWidget, 16)
    , mQuit(false)
{ }

void MenuScreen::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);
    
    if (Keys::ok(keyId))
    {
        if (event.pressed)
        {
            auto keyId(mDataSource[mMenuWidget.selectedIndex()].keyId);
            
            mEventManager.processKeyEvent(KeyEvent(keyId, true));
            
            mQuit = true;
        }
    }
    else if (Keys::cancel(keyId))
    {
        if (event.pressed)
        {
            mQuit = true;
        }
    }
    else if (Keys::up(keyId) ||
             Keys::down(keyId) ||
             Keys::pageUp(keyId) ||
             Keys::pageDown(keyId))
    {
        mMenuWidget.processKeyEvent(event);
    }
    else
    {
        mTitleWidget.processKeyEvent(event);
    }
}

void MenuScreen::poll()
{
    Surface::WidgetGuard guard(mSurface, mHSplit);
    
    AutoRepeat autoRepeat(mEventManager.timer,
                          *this);
    while (!mQuit)
    {
        mEventManager.poll(autoRepeat);
    }
}
