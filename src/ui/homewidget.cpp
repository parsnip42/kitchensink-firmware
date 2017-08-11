#include "ui/homewidget.h"

#include "ui/renderutil.h"

HomeWidget::Entry::Entry()
    : value(false)
    , visible(false)
{ }


HomeWidget::HomeWidget()
    : visible(true)
{ }

void HomeWidget::render(const RasterLine& rasterLine, int row)
{
    if (!visible)
    {
        return;
    }
    
    constexpr int widgetColumnCount = 3;
    
    auto widgetRow(row / mWidgetHeight);

    for (auto widgetColumn(0); widgetColumn < widgetColumnCount; ++widgetColumn)
    {
        std::size_t widgetIndex((widgetRow * widgetColumnCount) + widgetColumn);

        if (widgetIndex < entries.size())
        {
            auto& entry(entries[widgetIndex]);

            if (entry.visible)
            {
                RenderUtil::text(entry.text,
                                 mWidgetHeight + 1 + (widgetColumn * mWidgetWidth),
                                 row % Font::kHeight,
                                 rasterLine);

                if (entry.value)
                {
                    auto led(rasterLine.subset(widgetColumn * mWidgetWidth, mWidgetHeight));
                    
                    RenderUtil::fill(led, 0xf);
                }
            }
        }
    }
}

void HomeWidget::parented()
{
    auto size(widgetSize());

    mWidgetWidth = size.width / 3;
    mWidgetHeight = 12;
}
