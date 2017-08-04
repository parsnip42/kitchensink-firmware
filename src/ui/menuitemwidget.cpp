#include "ui/menuitemwidget.h"

#include "ui/renderutil.h"

MenuItemWidget::MenuItemWidget(const StrRef& nText,
                               const StrRef& nShortcut)
    : text(nText)
    , shortcut(nShortcut)
    , mFocused(true)
{ }

void MenuItemWidget::setFocused(bool focused)
{
    mFocused = focused;
}

void MenuItemWidget::render(const RasterLine& rasterLine, int row)
{
    uint8_t fg;
    uint8_t bg;

    if (mFocused)
    {
        fg = 0x0;
        bg = 0xf;
    }
    else
    {
        fg = 0x7;
        bg = 0x0;
    }

    auto size(widgetSize());

    if (shortcut.empty())
    {
        auto xOffset((size.width - (Font::kWidth * text.length())) / 2);
   
        if (mFocused)
        {
            RenderUtil::fill(rasterLine.subset(0, xOffset), bg);
            xOffset += RenderUtil::text(text, xOffset, row, rasterLine, fg, bg);
            RenderUtil::fill(rasterLine.subset(xOffset), bg);
        }
        else
        {
            RenderUtil::textPrefix(filter, text, xOffset, row, rasterLine, 0xf, fg, bg);
        }
    }
    else
    {
        auto nameOffset((size.width / 4) - (Font::kWidth * text.length() / 2));
        auto scOffset((3 * size.width / 4) - (Font::kWidth * shortcut.length() / 2));

        if (mFocused)
        {
            RenderUtil::fill(rasterLine.subset(0, nameOffset), bg);
            nameOffset += RenderUtil::text(text, nameOffset, row, rasterLine, fg, bg);
            RenderUtil::fill(rasterLine.subset(nameOffset, scOffset - nameOffset), bg);
            scOffset += RenderUtil::text(shortcut, scOffset, row, rasterLine, fg, bg);
            RenderUtil::fill(rasterLine.subset(scOffset), bg);
        }
        else
        {
            RenderUtil::textPrefix(filter, text, nameOffset, row, rasterLine, 0xf, fg, bg);
            RenderUtil::textPrefix(filter, shortcut, scOffset, row, rasterLine, 0xf, fg, bg);
        }
    }
}

