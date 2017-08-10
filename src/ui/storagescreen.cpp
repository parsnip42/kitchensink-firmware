#include "ui/storagescreen.h"

#include "keyevent.h"
#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/strostream.h"

StorageScreen::StorageScreen()
    : mItems({ mLabels[0], mLabels[1], mLabels[2], mLabels[3] })
    , mHStackWidget(mItems, true)
{ }

void StorageScreen::processKeyEvent(const KeyEvent& event)
{
    StrOStream out(mLabels[0].text);

    out.appendInt((int)event.keyId.type());
    out.appendStr(":");
    out.appendInt((int)event.keyId.value());
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
