#include "ui/labelwidget.h"

#include "types/strref.h"
#include "ui/surface.h"
#include "ui/rectangle.h"
#include "ui/renderutil.h"
#include "ui/font.h"
#include "ui/colors.h"

LabelWidget::LabelWidget(const StrRef& nText,
                         Justify       nJustify,
                         bool          nCanFocus)
    : text(nText)
    , justify(nJustify)
    , invert(false)
    , mCanFocus(nCanFocus)
    , mFocused(true)
{ }

bool LabelWidget::canFocus() const
{
    return mCanFocus;
}

void LabelWidget::setFocused(bool focused)
{
    mFocused = focused;
}

void LabelWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(widgetSize());
    
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

    auto fg((mFocused || !mCanFocus) ? Colors::kFocused : Colors::kUnfocused);
    auto bg(Colors::kBackground);
    
    if (invert)
    {
        std::swap(fg, bg);
    }
    
    RenderUtil::text(text, xOffset, row - yOffset, rasterLine, fg, bg);
}

Dimension LabelWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}
