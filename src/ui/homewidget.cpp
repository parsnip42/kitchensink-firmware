#include "ui/homewidget.h"

#include "ui/renderutil.h"

HomeWidget::Entry::Entry()
    : value(false)
    , visible(false)
{ }


HomeWidget::HomeWidget(int widgetColumns)
    : visible(true)
    , mWidgetWidth(0)
    , mWidgetHeight(0)
    , mWidgetColumns(widgetColumns)
{ }

void HomeWidget::render(const RasterLine& rasterLine, int row)
{
    if (!visible)
    {
        return;
    }

    int margin(1);
    
    auto widgetRow(row / (mWidgetHeight + margin));

    for (auto widgetColumn(0); widgetColumn < mWidgetColumns; ++widgetColumn)
    {
        std::size_t widgetIndex((widgetRow * mWidgetColumns) + widgetColumn);

        if (widgetIndex < entries.size())
        {
            auto& entry(entries[widgetIndex]);

            if (entry.visible)
            {
                auto region(rasterLine.subset(widgetColumn * mWidgetWidth, mWidgetWidth));
                auto entryRow(row % (mWidgetHeight + margin));

                if (entryRow < mWidgetHeight)
                {
                    renderIndicator(entry,
                                    region,
                                    entryRow);
                }
            }
        }
    }
}

void HomeWidget::parented()
{
    auto size(widgetSize());

    mWidgetWidth   = size.width / mWidgetColumns;
    mWidgetHeight  = Font::kHeight;
}

void HomeWidget::renderIndicator(const Entry&      entry,
                                 const RasterLine& rasterLine,
                                 int               row)
{
    auto entryRow(row % mWidgetHeight);
    auto margin(mWidgetHeight / 2);
                
    RenderUtil::text(entry.text,
                     mWidgetHeight + margin,
                     entryRow,
                     rasterLine);

    auto led(rasterLine.subset(0, mWidgetHeight));
                
    if (entryRow == 0 || entryRow == mWidgetHeight - 1)
    {
        RenderUtil::fill(led, 0xf);
    }
    else
    {
        led[0] = 0xf;
        led[mWidgetHeight - 1] = 0xf;
    }
                
    if (entryRow >= 2 && entryRow <= mWidgetHeight - 3)
    {
        if (entry.value)
        {
            RenderUtil::fill(led.subset(2, mWidgetHeight - 4), 0xf);
        }
    }

}
