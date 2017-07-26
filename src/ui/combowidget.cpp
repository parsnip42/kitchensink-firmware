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
        mSurface.paintText(region.x, region.y, "<", color, 0);
        mSurface.paintText(region.x + region.width - Surface::kFontWidth, region.y, ">", color, 0);
    }
    else
    {
        mSurface.clearRegion(region.x, region.y, Surface::kFontWidth, Surface::kFontHeight);
        mSurface.clearRegion(region.x + region.width - Surface::kFontWidth, region.y, Surface::kFontWidth, Surface::kFontHeight);

    }
    
    DataSource::ItemText text;

    mDataSource.item(text, selectedItem);
    
    mSurface.paintTextC(region.x + 20, region.y, region.width - 40, text, color, 0);
}

void ComboWidget::processKeyEvent(const KeyEvent& event)
{
    paintSelection();

    if (!event.pressed)
    {
        auto keyId(event.keyId);

        if (Keys::left(keyId))
        {
            selectedItem += mDataSource.size() - 1;
            selectedItem %= mDataSource.size();
            paintSelection();
        }
        
        if (Keys::right(keyId))
        {
            ++selectedItem %= mDataSource.size();
            paintSelection();
        }
    }
}

void ComboWidget::paintSelection()
{
    DataSource::ItemText text;

    mDataSource.item(text, selectedItem);
    
    mSurface.paintTextC(region.x + Surface::kFontWidth, region.y, region.width - (Surface::kFontWidth * 2), text, 0xf, 0);
}
