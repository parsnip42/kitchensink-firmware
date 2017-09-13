#include "ui/eventstreamscreen.h"

#include "event/event.h"
#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/stroutstream.h"
#include "serialize/eventserializer.h"

#include <elapsedMillis.h>

EventStreamScreen::EventStreamScreen()
    : mItems({ mLabels[0], mLabels[1], mLabels[2], mLabels[3] })
    , mHStackWidget(mItems, true)
{ }

bool EventStreamScreen::processEvent(const Event& event)
{
    if (mEvents.size() >= 4)
    {
        mEvents.popBack();
    }

    mEvents.pushFront(event);

    int index(0);
    auto it(mEvents.begin());

    while (it != mEvents.end() && index < 4)
    {
        StrOutStream out(mLabels[index].text);

        out.reset();

        out.appendInt(millis());
        out.appendStr(" : ");
        EventSerializer::serializeReadable(*it, out);
        out.appendStr(" / ");
        out.appendInt(event.data(), "%4.4x");

        mLabels[index].invalidateWidget();
        
        ++index;
        ++it;
    }

    return false;
}

Widget& EventStreamScreen::rootWidget()
{
    return mHStackWidget;
}
