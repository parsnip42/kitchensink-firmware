#include "ui/menuscreen.h"

#include "autorepeat.h"
#include "eventmanager.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"

namespace
{

MenuItemWidget createMenuItem(const MenuScreen::Item& item, std::size_t)
{
    return MenuItemWidget(item.title, item.shortcut);
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
    , mHSplit(mTitleWidget,
              mMenuWidget,
              MenuTitleWidget::kPreferredHeight)
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
            mEventManager.processKeyEvent(KeyEvent(keyId, false));
            
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
        mMenuWidget.filterIndex.filter(
            mDataSource.size(),
            [&](std::size_t index)
            {
                auto item = mDataSource[index];
                
                return (StrRef(item.title).beginsWithCase(mTitleWidget.filter()) ||
                        StrRef(item.shortcut).beginsWithCase(mTitleWidget.filter()));
            });
        
        mMenuWidget.filterStr = mTitleWidget.filter();
        mMenuWidget.update();
    }
}

void MenuScreen::poll()
{
    EventManager::RefocusGuard guardB(mEventManager);
    
    AutoRepeat autoRepeat(mEventManager.timer,
                          *this);

    Surface::WidgetGuard guard(mSurface, mHSplit);
    
    while (!mQuit)
    {
        mEventManager.poll(autoRepeat);
    }
}
