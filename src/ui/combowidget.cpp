#include "ui/combowidget.h"

#include "autorepeat.h"
#include "ui/surface.h"
#include "ui/keys.h"
#include "ui/rectangle.h"
#include "types/strref.h"
#include "eventmanager.h"

ComboWidget::ComboWidget(Surface&                 surface,
                         EventManager&            eventManager,
                         ComboWidget::DataSource& dataSource)
    : selectedItem(0)
    , mSurface(surface)
    , mEventManager(eventManager)
    , mDataSource(dataSource)
{ }

void ComboWidget::redrawContent(bool focused)
{
    uint8_t color(focused ? 0xf : 0x4);

    if (focused)
    {
        mSurface.paintTextL(region.x, region.y, 6, "<", color, 0);
        mSurface.paintText(region.x + region.width - Surface::kFontWidth, region.y, ">", color, 0);
    }
    else
    {
        mSurface.clearRegion(region.x, region.y, Surface::kFontWidth, Surface::kFontHeight, 0x0);
        mSurface.clearRegion(region.x + region.width - Surface::kFontWidth, region.y, Surface::kFontWidth, Surface::kFontHeight, 0x0);

    }
    
    paintSelection(color);
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
            paintSelection(0xf);
        }

        if (Keys::right(keyId))
        {
            ++selectedItem %= mDataSource.size();
            paintSelection(0xf);
        }
    }
}

void ComboWidget::paintSelection(uint8_t color)
{
    DataSource::ItemText text;

    mDataSource.item(text, selectedItem);
    
    mSurface.paintTextC(region.x + 20,
                        region.y,
                        region.width - 40,
                        text,
                        color,
                        0);
}
