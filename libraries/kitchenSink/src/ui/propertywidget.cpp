#include "ui/propertywidget.h"
#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"

PropertyWidget::PropertyWidget(const StrRef& nKey,
                               int           nSeparation,
                               const StrRef& nValue)
    : separation(nSeparation)
    , key(nKey)
    , value(nValue)
{ }

void PropertyWidget::render(const RasterLine& rasterLine, int row)
{
    RenderUtil::text(key, 0, row, rasterLine, Colors::kUnfocused, Colors::kBackground);
    RenderUtil::text(value, separation, row, rasterLine, Colors::kFocused, Colors::kBackground);
}

Dimension PropertyWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}
