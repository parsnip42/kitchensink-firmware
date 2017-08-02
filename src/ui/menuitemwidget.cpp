#include "ui/menuitemwidget.h"

#include "ui/renderutil.h"

MenuItemWidget::MenuItemWidget(const StrRef& nText)
    : text(nText)
    , mFocused(true)
{ }

void MenuItemWidget::setFocused(bool focused)
{
    mFocused = focused;
}

void MenuItemWidget::render(const RasterLine& rasterLine, int row)
{
    uint8_t fg(0xf);
    uint8_t bg(0x0);

    if (mFocused)
    {
        std::swap(fg, bg);
    }

    auto size(getSize());
    auto xOffset((size.width - (Font::kWidth * text.length())) / 2);

    RenderUtil::fill(rasterLine.subset(0, xOffset), bg);
    auto xEnd(RenderUtil::render(text, xOffset, row, rasterLine, fg, bg));
    RenderUtil::fill(rasterLine.subset(xEnd), bg);
}
