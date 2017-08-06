#include "ui/storagescreen.h"

#include "ui/keys.h"
#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/strostream.h"
#include "eventmanager.h"

StorageScreen::StorageScreen(Surface&      surface,
                             EventManager& eventManager)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mTitleWidget("Storage")
    , mStatusLabel(">")
    , mWidgetSet({ &mStatusLabel })
    , mListWidget(mWidgetSet.begin(), mWidgetSet.end(), LabelWidget::kPreferredHeight)
    , mHSplit(mTitleWidget,
              mListWidget,
              TitleWidget::kPreferredHeight + 1)
    , mQuit(false)
{ }

void StorageScreen::processKeyEvent(const KeyEvent& event)
{
    if (event.pressed)
    {
        auto keyId(event.keyId);
        
        if (Keys::ok(keyId) || Keys::cancel(keyId))
        {
            mQuit = true;
        }
    }

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

void StorageScreen::poll()
{
    EventManager::RefocusGuard guardB(mEventManager);
    
    Surface::WidgetGuard guard(mSurface, mHSplit);

    while (!mQuit)
    {
        mEventManager.poll(*this);
    }

    // mTextScreen.init();

    // mTextScreen.appendLine("Reading SD Card");

    // Storage storage;
    
    // if (storage.state())
    // {
    //     StrBuf<48> sdErr;

    //     StrOStream out(sdErr);
        
    //     out.appendStr("SD Failed : ")
    //        .appendInt(storage.state());

    //     mTextScreen.appendLine(sdErr);
    // }
    // else
    // {
    //     StrBuf<48> sdInfo;
    //     StrOStream out(sdInfo);
        
    //     out.appendStr("SD OK : ")
    //        .appendInt(storage.capacityMb())
    //        .appendStr("MB / FAT")
    //        .appendInt(storage.fatType());
        
    //     mTextScreen.appendLine(sdInfo);
    // }
    
    // while (!mQuit)
    // {
    //     mEventManager.poll(*this);
    // }
}
