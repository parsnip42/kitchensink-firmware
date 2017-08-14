#include "ui/storagescreen.h"

#include "event/event.h"
#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/strostream.h"

StorageScreen::StorageScreen()
    : mItems({ mLabels[0], mLabels[1], mLabels[2], mLabels[3] })
    , mHStackWidget(mItems, true)
{ }

void StorageScreen::processEvent(const Event& event)
{
    StrOStream out(mLabels[0].text);

    out.appendInt((int)event.type());
    out.appendStr(":");
    out.appendInt((int)event.subType());
    out.appendStr(":");
    out.appendInt((int)event.value());
    out.appendStr(" ");
    mLabels[0].invalidateWidget();

    if (mLabels[0].text.length() > 40)
    {
        mLabels[0].text = "";
    }
}

Widget& StorageScreen::rootWidget()
{
    return mHStackWidget;
}
