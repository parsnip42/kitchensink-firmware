#include "ui/combowidget.h"

#include "autorepeat.h"
#include "ui/keys.h"
#include "ui/rectangle.h"
#include "ui/renderutil.h"
#include "ui/widgetcontainer.h"
#include "types/strref.h"

ComboWidget::ComboWidget(ComboWidget::DataSource& dataSource)
    : selectedItem(0)
    , focused(false)
    , mDataSource(dataSource)
{ }

void ComboWidget::processKeyEvent(const KeyEvent& event)
{
    if (!event.pressed)
    {
        auto keyId(event.keyId);

        if (Keys::left(keyId))
        {
            selectedItem += mDataSource.size() - 1;
            selectedItem %= mDataSource.size();
            invalidateWidget();
        }

        if (Keys::right(keyId))
        {
            ++selectedItem %= mDataSource.size();
            invalidateWidget();
        }
    }
}

void ComboWidget::setFocused(bool nFocused)
{
    focused = nFocused;
    invalidateWidget();
}

void ComboWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(getSize());
    
    uint8_t fg(focused ? 0xf : 0x7);

    auto yOffset(0);
    
    if (Font::kHeight < size.height)
    {
        yOffset = (size.height - Font::kHeight) / 2;
    }

    DataSource::ItemText text;

    mDataSource.item(text, selectedItem);

    auto xOffset((size.width - (Font::kWidth * text.length())) / 2);

    RenderUtil::render(text,
                       xOffset,
                       row - yOffset,
                       rasterLine,
                       fg,
                       0x0);

    if (row >= 3 && row <= size.height - 3)
    {
        int halfHeight(size.height / 2);
        
        for (int x(0); x < halfHeight; ++x)
        {
            auto xOffset(x);
            int yDistance(abs(halfHeight - row));
            
            rasterLine[xOffset] = (x > yDistance && x < yDistance + 2) ? fg : 0x0;
            rasterLine[xOffset + (size.width - halfHeight)] = ((halfHeight - x) > yDistance && (halfHeight - x) < yDistance + 2) ? fg : 0x0;
        }
    }
}

















