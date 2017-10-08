#include "ui/titlewidget.h"

#include "ui/renderutil.h"

TitleWidget::TitleWidget(const StrRef& nText)
    : text(nText)
{ }

void TitleWidget::render(const RasterLine& rasterLine, int row)
{
    RenderUtil::text(text, 0, row, rasterLine, 0xf, 0x0);

    if (row == Font::kHeight + 1)
    {
        RenderUtil::fill(rasterLine, 0xf);
    }
}
