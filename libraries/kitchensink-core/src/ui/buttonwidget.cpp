#include "ui/buttonwidget.h"

#include "ui/font.h"
#include "ui/keys.h"
#include "ui/colors.h"
#include "ui/renderutil.h"

ButtonWidget::ButtonWidget(const StrRef& nText)
    : text(nText)
    , mFocused(true)
{ }

bool ButtonWidget::processEvent(const Event& event)
{
    if (Keys::ok(event))
    {
        activated.fireAction();
        
        return true;
    }

    return false;
}

void ButtonWidget::setFocused(bool focused)
{
    mFocused = focused;
}

void ButtonWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(widgetSize());

    auto xOffset((size.width - (Font::kWidth * text.length())) / 2);

    auto yOffset(0);

    if (Font::kHeight < size.height)
    {
        yOffset = (size.height - Font::kHeight) / 2;
    }

    uint8_t fg(Colors::kBlack);
    uint8_t bg(mFocused ? Colors::kFocused : Colors::kUnfocused);

    RenderUtil::fill(rasterLine.subset(xOffset / 3, xOffset * 2 / 3), bg);
    xOffset += RenderUtil::text(text, xOffset, row - yOffset, rasterLine, fg, bg);

    auto trailing(rasterLine.subset(xOffset, (rasterLine.size() - xOffset) * 2 / 3));
    RenderUtil::fill(trailing, bg);
}

Dimension ButtonWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}
