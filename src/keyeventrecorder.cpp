#include "keyeventrecorder.h"


KeyEventRecorder::KeyEventRecorder(bool           realtime,
                                   KeyEventStage& next)
    : mRealtime(realtime)
    , mContent()
    , mSize(0)
    , mComplete(false)
    , mNext(next)
{ }

void KeyEventRecorder::processKeyEvent(const KeyEvent& event)
{
    if (event.keyId != KeyId::Action(KeyId::ActionType::kMenu, 0))
    {
        if (mSize < mContent.size())
        {
            mContent[mSize++] = event;
        }
        
        mNext.processKeyEvent(event);
    }
    else
    {
        mComplete = true;
    }
}







