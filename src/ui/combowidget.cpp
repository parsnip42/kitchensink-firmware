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

bool ComboWidget::processEvent(const Event& event)
{
    if (Keys::left(event))
    {
        selectedItem += mDataSource.size() - 1;
        selectedItem %= mDataSource.size();
        invalidateWidget();
    }
    else if (Keys::right(event))
    {
        ++selectedItem %= mDataSource.size();
        invalidateWidget();
    }
    else
    {
        return false;
    }
    
    return true;
}

void ComboWidget::setFocused(bool nFocused)
{
    focused = nFocused;
}

void ComboWidget::render(const RasterLine& rasterLine, int row)
{
    auto size(widgetSize());
    
    uint8_t fg(focused ? 0xf : 0x7);

    auto yOffset(0);
    
    if (Font::kHeight < size.height)
    {
        yOffset = (size.height - Font::kHeight) / 2;
    }

    auto text(mDataSource[selectedItem]);
    auto xOffset((size.width - (Font::kWidth * text.length())) / 2);

    RenderUtil::text(text,
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

















