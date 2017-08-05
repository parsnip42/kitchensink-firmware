#include "ui/recordmacroscreen.h"

#include "keyprocessor.h"
#include "macro.h"
#include "ui/surface.h"
#include "types/strostream.h"
#include "keyeventrecorder.h"
#include "eventmanager.h"

#include <cstdint>

RecordMacroScreen::RecordMacroScreen(Surface&       surface,
                                     EventManager&  eventManager,
                                     Macro&         macro,
                                     bool           realtime)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mMacro(macro)
    , mRecorder(realtime)
    , mTitleWidget("Recording Macro")
    , mLabelWidget("Recording",
                   Justify::kCenter)
    , mHSplit(mTitleWidget,
              mLabelWidget,
              TitleWidget::kPreferredHeight)
    , mFlashTimer(eventManager.timer.createHandle())
    , mFlash(true)
{ }

void RecordMacroScreen::poll()
{
    Surface::WidgetGuard guard(mSurface, mHSplit);

    mFlashTimer.scheduleRepeating(500, 500);

    while (!mRecorder.complete())
    {
        mEventManager.poll(*this);
    }
}

void RecordMacroScreen::processKeyEvent(const KeyEvent& event)
{
    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;

        if (mRecorder.full())
        {
            mLabelWidget.text = "Macro Storage Full";
            mFlashTimer.cancel();
        }
        else
        {
            mLabelWidget.text = mFlash ? "Recording" : "";
        }
        
        mLabelWidget.invalidateWidget();
        return;
    }

    mEventManager.defaultOutput.processKeyEvent(event);
    mRecorder.processKeyEvent(event);

    if (mRecorder.complete())
    {
        mMacro.content.assign(mRecorder.begin(),
                              mRecorder.end());
    }
}
