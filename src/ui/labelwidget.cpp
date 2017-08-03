#include "ui/labelwidget.h"

#include "types/strref.h"
#include "ui/surface.h"
#include "ui/rectangle.h"
#include "ui/renderutil.h"
#include "ui/font.h"

LabelWidget::LabelWidget(const StrRef& nText,
                         Justify       nJustify)
    : text(nText)
    , justify(nJustify)
    , mFocused(true)
{ }

void LabelWidget::setFocused(bool focused)
{
    mFocused = focused;
}

void LabelWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(getSize());
    
    auto xOffset(0);
    
    switch (justify)
    {
    case Justify::kRight:
        xOffset = size.width - (Font::kWidth * text.length());
        break;
        
    case Justify::kCenter:
        xOffset = (size.width - (Font::kWidth * text.length())) / 2;
        break;
        
    default:
        break;
    }

    auto yOffset(0);

    if (Font::kHeight < size.height)
    {
        yOffset = (size.height - Font::kHeight) / 2;
    }

    uint8_t fg(mFocused ? 0xf : 0x7);

    RenderUtil::render(text, xOffset, row - yOffset, rasterLine, fg, 0x0);
}
