#include "ui/menuscreen.h"

#include "event/event.h"
#include "event/screenevent.h"
#include "ui/keys.h"
#include "ui/menuitemwidget.h"

MenuScreen::MenuScreen(const DataSource& dataSource,
                       EventStage&       next)
    : mMenuWidget(dataSource)
    , mNext(next)
{ }

void MenuScreen::processEvent(const Event& event)
{
    if (Keys::ok(event))
    {
        auto event(mMenuWidget.selectedItem().event);

        if (!event.is<ScreenEvent>())
        {
            mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome, 0));
        }
        
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
