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

bool MenuScreen::processEvent(const Event& event)
{
    if (Keys::ok(event))
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
    else 
    {
        return mMenuWidget.processEvent(event);
    }

    return true;
}

Widget& MenuScreen::rootWidget()
{
    return mMenuWidget;
}
