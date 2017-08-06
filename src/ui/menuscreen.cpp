#include "ui/menuscreen.h"

#include "autorepeat.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"
#include "ui/screenstack.h"

namespace
{

MenuItemWidget createMenuItem(const MenuScreen::Item& item, std::size_t)
{
    return MenuItemWidget(item.title, item.shortcut);
}

}

MenuScreen::MenuScreen(const StrRef&     title,
                       const DataSource& dataSource,
                       ScreenStack&      screenStack,
                       Timer&            timer,
                       KeyEventStage&    next)
    : mTitle(title)
    , mDataSource(dataSource)
    , mMenuDataSource(dataSource, &createMenuItem)
    , mMenuWidget(mMenuDataSource)
    , mTitleWidget(title, timer)
    , mHSplit(mTitleWidget,
              mMenuWidget,
              MenuTitleWidget::kPreferredHeight)
    , mScreenStack(screenStack)
    , mNext(next)
{ }

void MenuScreen::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (Keys::ok(keyId))
    {
        if (event.pressed)
        {
            auto keyId(mDataSource[mMenuWidget.filterIndex[mMenuWidget.selectedIndex()]].keyId);
            
            mScreenStack.pop();
            mNext.processKeyEvent(KeyEvent(keyId, true));
            mNext.processKeyEvent(KeyEvent(keyId, false));
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
        mMenuWidget.processKeyEvent(event);
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
