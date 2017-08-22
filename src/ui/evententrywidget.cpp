#include "ui/evententrywidget.h"

#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"
#include "ui/keys.h"
#include "serialize/eventserializer.h"
#include "event/tickevent.h"

EventEntryWidget::EventEntryWidget(Timer& timer)
    : mFlashTimer(timer.createHandle())
    , mEventStr("<Unset>")
    , mFocused(true)
    , mFlash(true)
{
    mFlashTimer.scheduleRepeating(250, 250);
}

void EventEntryWidget::processEvent(const Event& inEvent)
{
    if (mFlashTimer.matches(inEvent))
    {
        mFlash = !mFlash;
        invalidateWidget();
    }
    else if (Keys::ok(inEvent))
    {
        
    }
    else if (!inEvent.is<TickEvent>())
    {
        if (!inEvent.inverted())
        {
            event = inEvent;
            update();
        }
    }
}

void EventEntryWidget::setFocused(bool focused)
{
    mFocused = focused;
    mFlash   = false;
}

void EventEntryWidget::render(const RasterLine& rasterLine, int row)
{
    auto fg(mFocused ? Colors::kBlack : Colors::kWhite);
    auto bg(mFocused ? Colors::kWhite : Colors::kBlack);

    if (mFlash)
    {
        std::swap(fg, bg);
    }

    mEventStr.clear();
    
    EventSerializer::serializeReadable(event, mEventStr);

    RenderUtil::text(mEventStr, 0, row, rasterLine, fg, bg);
}

Dimension EventEntryWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}

void EventEntryWidget::update()
{
    
    invalidateWidget();
}
