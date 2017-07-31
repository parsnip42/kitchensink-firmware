#include "ui/combowidget.h"

#include "autorepeat.h"
#include "ui/surface.h"
#include "ui/keys.h"
#include "ui/rectangle.h"
#include "ui/widgetcontainer.h"
#include "types/strref.h"
#include "eventmanager.h"

ComboWidget::ComboWidget(Surface&                 surface,
                         EventManager&            eventManager,
                         WidgetContainer&         parent,
                         ComboWidget::DataSource& dataSource)
    : selectedItem(0)
    , focused(false)
    , mSurface(surface)
    , mEventManager(eventManager)
    , mParent(parent)
    , mDataSource(dataSource)
{ }

void ComboWidget::setFocused(bool nFocused)
{
    focused = nFocused;
    mParent.invalidateWidget(*this, region);
}

void ComboWidget::processKeyEvent(const KeyEvent& event)
{
    if (!event.pressed)
    {
        auto keyId(event.keyId);

        if (Keys::left(keyId))
        {
            selectedItem += mDataSource.size() - 1;
            selectedItem %= mDataSource.size();
            mParent.invalidateWidget(*this, region);
        }

        if (Keys::right(keyId))
        {
            ++selectedItem %= mDataSource.size();
            mParent.invalidateWidget(*this, region);
        }
    }
}

void ComboWidget::render(Surface::RowData& rowData, int row)
{
    uint8_t fg(focused ? 0xf : 0x7);

    auto yOffset(0);
    
    if (Font::kHeight < region.height)
    {
        yOffset = (region.height - Font::kHeight) / 2;
    }

    DataSource::ItemText text;

    mDataSource.item(text, selectedItem);

    auto xOffset((region.width - (Font::kWidth * text.length())) / 2);

    Surface::render(text,
                    region.x + xOffset,
                    row - yOffset,
                    rowData,
                    fg,
                    0x0);

    if (row >= 3 && row <= region.height - 3)
    {
        int halfHeight(region.height / 2);
        
        for (int x(0); x < halfHeight; ++x)
        {
            auto xOffset(region.x + x);
            int yDistance(abs(halfHeight - row));
            
            rowData[xOffset] = (x > yDistance && x < yDistance + 2) ? fg : 0x0;
            rowData[xOffset + (region.width - halfHeight)] = ((halfHeight - x) > yDistance && (halfHeight - x) < yDistance + 2) ? fg : 0x0;
        }
    }
}

















