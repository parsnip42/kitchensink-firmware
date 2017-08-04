#include "ui/menuscreen.h"

#include "autorepeat.h"
#include "eventmanager.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"

namespace
{

MenuItemWidget createMenuItem(const MenuScreen::Item& item, std::size_t)
{
    MenuItemWidget widget;
    
    widget.text = item.title;

    return widget;
}

}

MenuScreen::MenuScreen(const StrRef&     title,
                       const DataSource& dataSource,
                       Surface&          surface,
                       EventManager&     eventManager)
    : mTitle(title)
    , mSurface(surface)
    , mEventManager(eventManager)
    , mDataSource(dataSource)
    , mMenuDataSource(dataSource, &createMenuItem)
    , mMenuWidget(mMenuDataSource)
    , mTitleWidget(title, eventManager)
    , mHSplit(mTitleWidget, mMenuWidget, 16)
    , mQuit(false)
{ }

void MenuScreen::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kTick)
    {
        mMenuWidget.processKeyEvent(event);
        mTitleWidget.processKeyEvent(event);
    }
    else if (Keys::ok(keyId))
    {
        if (event.pressed)
        {
            auto keyId(mDataSource[mMenuWidget.filterIndex[mMenuWidget.selectedIndex()]].keyId);
            
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
        mMenuWidget.filterIndex.filter(mDataSource.size(),
                                       [&](std::size_t index)
                                       {
                                           auto item = mDataSource[index];

                                           return StrRef(item.title).beginsWithCase(mTitleWidget.filter());
                                       });

        mMenuWidget.update();
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





