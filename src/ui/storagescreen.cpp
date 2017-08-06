#include "ui/storagescreen.h"

#include "keyevent.h"
#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/strostream.h"

StorageScreen::StorageScreen()
    : mTitleWidget("Storage")
    , mStatusLabel(">")
    , mWidgetSet({ &mStatusLabel })
    , mListWidget(mWidgetSet.begin(), mWidgetSet.end(), LabelWidget::kPreferredHeight)
    , mHSplit(mTitleWidget,
              mListWidget,
              TitleWidget::kPreferredHeight + 1)
{ }

void StorageScreen::processKeyEvent(const KeyEvent& event)
{
    StrOStream out(mStatusLabel.text);

    out.appendInt((int)event.keyId.type());
    out.appendStr(":");
    out.appendInt((int)event.keyId.value());
    out.appendStr(" ");
    mStatusLabel.invalidateWidget();

    if (mStatusLabel.text.length() > 40)
    {
        mStatusLabel.text = "";
    }
}

Widget& StorageScreen::rootWidget()
{
    return mHSplit;
}
