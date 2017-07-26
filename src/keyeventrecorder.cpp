#include "keyeventrecorder.h"

#include <elapsedMillis.h>

KeyEventRecorder::KeyEventRecorder(bool realtime)
    : mLastMs(0)
    , mRealtime(realtime)
    , mContent()
    , mSize(0)
    , mComplete(false)
{ }

void KeyEventRecorder::processKeyEvent(const KeyEvent& event)
{
    if (event.keyId != KeyId::Action(KeyId::ActionType::kMenu, 0))
    {
        if (event.keyId.type() != KeyId::Type::kTick)
        {
            if (mSize < mContent.size())
            {
                if (mRealtime)
                {
                    auto nowMs(millis());
                    
                    if (mLastMs != 0)
                    {
                        mContent[mSize++] = KeyEvent(KeyId::Delay(nowMs - mLastMs));    
                    }
                    
                    mLastMs = nowMs;
                }
            }
            
            if (mSize < mContent.size())
            {
                mContent[mSize++] = event;
            }
        }
    }
    else
    {
        mComplete = true;
    }
}







