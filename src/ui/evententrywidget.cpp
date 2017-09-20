#include "ui/evententrywidget.h"

#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"
#include "ui/keys.h"
#include "serialize/eventserializer.h"
#include "event/tickevent.h"

EventEntryWidget::EventEntryWidget(Timer& timer)
    : mFlashTimer(timer.createHandle())
    , mFocused(true)
    , mFlash(true)
    , mTrigger(false)
{
    mFlashTimer.scheduleRepeating(250, 250);
}

bool EventEntryWidget::processEvent(const Event& inEvent)
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

void EventEntryWidget::setFocused(bool focused)
{
    mFocused = focused;
    mFlash   = false;

    if (!mFocused)
    {
        mTrigger = false;
    }
}

void EventEntryWidget::render(const RasterLine& rasterLine,
                              int               row)
{
    auto fg(mFocused ? Colors::kFocused : Colors::kUnfocused);
    auto bg(Colors::kBlack);

    if (mFocused && mTrigger && mFlash)
    {
        std::swap(fg, bg);
    }

    StrBuf<24> eventStr;

    EventSerializer::serializeReadable(event, eventStr);

    RenderUtil::text(eventStr, 0, row, rasterLine, fg, bg);
}

Dimension EventEntryWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}

void EventEntryWidget::update()
{
    invalidateWidget();
}
