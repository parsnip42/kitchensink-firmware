#include "ui/menuscreen.h"

#include "event/event.h"
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
                       EventStage&       next)
    : mDataSource(dataSource)
    , mMenuDataSource(dataSource, &createMenuItem)
    , mMenuWidget(mMenuDataSource)
    , mScreenStack(screenStack)
    , mNext(next)
{ }

void MenuScreen::processEvent(const Event& event)
{
    if (Keys::ok(event))
    {
        auto event(mDataSource[mMenuWidget.filterIndex[mMenuWidget.selectedIndex()]].event);
            
        mScreenStack.pop();
        mNext.processEvent(event);
        mNext.processEvent(event.invert());
    }
    else 
    {
        mMenuWidget.processEvent(event);
    }
}

Widget& MenuScreen::rootWidget()
{
    return mMenuWidget;
}
