#include "ui/storagescreen.h"

#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/strostream.h"
#include "eventmanager.h"

StorageScreen::StorageScreen(Surface&      surface,
                             EventManager& eventManager)
    : mEventManager(eventManager)
    , mTextScreen(surface)
    , mQuit(false)
{ }

void StorageScreen::processKeyEvent(const KeyEvent& event)
{
    if (event.pressed)
    {
        mQuit = true;
    }
}

void StorageScreen::poll()
{
    mTextScreen.init();

    mTextScreen.appendLine("Reading SD Card");

    Storage storage;
    
    if (storage.state())
    {
        StrBuf<48> sdErr;

        StrOStream out(sdErr);
        
        out.appendStr("SD Failed : ")
           .appendInt(storage.state());

        mTextScreen.appendLine(sdErr);
    }
    else
    {
        StrBuf<48> sdInfo;
        StrOStream out(sdInfo);
        
        out.appendStr("SD OK : ")
           .appendInt(storage.capacityMb())
           .appendStr("MB / FAT")
           .appendInt(storage.fatType());
        
        mTextScreen.appendLine(sdInfo);
    }
    
    while (!mQuit)
    {
        mEventManager.poll(*this);
    }
}
