#include "ui/evententrywidget.h"

#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"
#include "serialize/eventserializer.h"

EventEntryWidget::EventEntryWidget()
    : mFocused(true)
{ }

void EventEntryWidget::processEvent(const Event& inEvent)
{
    event = inEvent;
    update();
}

void EventEntryWidget::setFocused(bool focused)
{
    mFocused = focused;
}

void EventEntryWidget::render(const RasterLine& rasterLine, int row)
{
    auto fg(mFocused ? Colors::kBlack : Colors::kWhite);
    auto bg(mFocused ? Colors::kWhite : Colors::kBlack);
    
    RenderUtil::text(mEventStr, 0, row, rasterLine, fg, bg);
}

Dimension EventEntryWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}

void EventEntryWidget::update()
{
    mEventStr.clear();
    EventSerializer::serialize(event, mEventStr);
    
    invalidateWidget();
}
