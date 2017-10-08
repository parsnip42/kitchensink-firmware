#include "ui/menuscreen.h"

#include "event/event.h"
#include "event/screenevent.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"

MenuScreen::MenuScreen(const DataSource& dataSource,
                       EventStage&       next)
    : mMenuWidget(dataSource)
    , mNext(next)
{
    mMenuWidget.itemSelected = Action::memFn<MenuScreen,
                                             &MenuScreen::onItemSelected>(this);
}

bool MenuScreen::processEvent(const Event& event)
{
    return mMenuWidget.processEvent(event);
}

Widget& MenuScreen::rootWidget()
{
    return mMenuWidget;
}

void MenuScreen::onItemSelected()
{
    auto event(mMenuWidget.selectedItem().event);

    mNext.processEvent(event);
    
    auto inverted(event.invert());
    
    if (inverted != Event())
    {
        mNext.processEvent(inverted);
    }
    
    if (!event.is<ScreenEvent>())
    {
        screenCompleted.fireAction();
    }
}
