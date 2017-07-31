#include "labelwidget.h"

#include "types/strref.h"
#include "ui/surface.h"
#include "ui/rectangle.h"
#include "ui/font.h"

LabelWidget::LabelWidget(const StrRef&    nText,
                         Justify          nJustify)
    : text(nText)
    , justify(nJustify)
    , focused(true)
{ }

void LabelWidget::setFocused(bool nFocused)
{
    focused = nFocused;
}

void LabelWidget::render(Surface::RowData& rowData, int row) const
{
    auto xOffset(region.x);
    
    switch (justify)
    {
    case Justify::kRight:
        xOffset = (region.x + region.width) - (Font::kWidth * text.length());
        break;
        
    case Justify::kCenter:
        xOffset = ((region.x + region.width) - (Font::kWidth * text.length())) / 2;
        break;
        
    default:
        break;
    }

    auto yOffset(0);

    if (Font::kHeight < region.height)
    {
        yOffset = (region.height - Font::kHeight) / 2;
    }

    uint8_t fg(focused ? 0xf : 0x7);

    Surface::render(text, xOffset, row - yOffset, rowData, fg, 0x0);
}
