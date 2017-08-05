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
    , mLabelWidget("Recording")
    , mHSplit(mTitleWidget,
              mLabelWidget,
              TitleWidget::kPreferredHeight)

{ }

void RecordMacroScreen::poll()
{
    Surface::WidgetGuard guard(mSurface, mTitleWidget);
    
    while (!mRecorder.complete())
    {
        mEventManager.poll(*this);
    }
}

void RecordMacroScreen::processKeyEvent(const KeyEvent& event)
{
    mEventManager.defaultOutput.processKeyEvent(event);
    mRecorder.processKeyEvent(event);

    if (!mRecorder.full())
    {
        // mSurface.paintText(0, 20, text, 0x7, 0);
    }
    else
    {
        // mSurface.paintText(0, 40, "Macro Full", 0xf, 0);
    }

    if (mRecorder.complete())
    {
        mMacro.content.assign(mRecorder.begin(),
                              mRecorder.end());
    }
}
