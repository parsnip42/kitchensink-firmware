#include "ui/storagescreen.h"

#include "event/event.h"
#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/stroutstream.h"
#include "serialize/eventserializer.h"

StorageScreen::StorageScreen()
    : mItems({ mLabels[0], mLabels[1], mLabels[2], mLabels[3] })
    , mHStackWidget(mItems, true)
{ }

bool StorageScreen::processEvent(const Event& event)
{
    StrOutStream out(mLabels[0].text);

    EventSerializer::serializeReadable(event, out);

    out.appendStr(" ");

    mLabels[0].invalidateWidget();

    if (mLabels[0].text.length() > 40)
    {
        mLabels[0].text = "";
    }

    return false;
}

Widget& StorageScreen::rootWidget()
{
    return mHStackWidget;
}
