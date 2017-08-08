#include "ui/menuscreen.h"

#include "keyevent.h"
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

MenuScreen::MenuScreen(const DataSource& dataSource,
                       ScreenStack&      screenStack,
                       KeyEventStage&    next)
    : mDataSource(dataSource)
    , mMenuDataSource(dataSource, &createMenuItem)
    , mMenuWidget(mMenuDataSource)
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
    else 
    {
        mMenuWidget.processKeyEvent(event);
    }
}

Widget& MenuScreen::rootWidget()
{
    return mMenuWidget;
}
