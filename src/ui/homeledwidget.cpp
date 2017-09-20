#include "ui/homeledwidget.h"

#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"
#include "ui/keys.h"
#include "serialize/eventserializer.h"
#include "event/tickevent.h"

HomeLedWidget::HomeLedWidget(Timer& timer)
    : mFlashTimer(timer.createHandle())
    , mEventStr("<Unset>")
    , mFocused(true)
    , mFlash(true)
    , mTrigger(false)
{
    mFlashTimer.scheduleRepeating(250, 250);
}

bool HomeLedWidget::processEvent(const Event& inEvent)
{
    if (mFlashTimer.matches(inEvent))
    {
        mFlash = !mFlash;
        invalidateWidget();

        return true;
    }
    else if (mTrigger)
    {
        if (inEvent.isUserEvent() &&
            !inEvent.is<ScreenEvent>() &&
            !inEvent.inverted())
        {
            mTrigger = false;
            event = inEvent;
            invalidateWidget();
            eventSelected.fireAction();

            return true;
        }
    }
    else if (Keys::ok(inEvent))
    {
        mTrigger = true;
        invalidateWidget();

        return true;
    }
    
    return false;
}

void HomeLedWidget::setFocused(bool focused)
{
    mFocused = focused;
    mFlash   = false;

    if (!mFocused)
    {
        mTrigger = false;
    }
}

void HomeLedWidget::render(const RasterLine& rasterLine,
                              int               row)
{
    auto fg(mFocused ? Colors::kFocused : Colors::kUnfocused);
    auto bg(Colors::kBlack);

    if (mFocused && mTrigger && mFlash)
    {
        std::swap(fg, bg);
    }

    mEventStr.clear();
    
    EventSerializer::serializeReadable(event, mEventStr);

    RenderUtil::text(mEventStr, 0, row, rasterLine, fg, bg);
}

Dimension HomeLedWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}

void HomeLedWidget::update()
{
    invalidateWidget();
}
