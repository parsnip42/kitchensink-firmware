#include "combo.h"

#include "autorepeat.h"
#include "keyprocessor.h"
#include "ui/surface.h"
#include "ui/keys.h"
#include "ui/rectangle.h"
#include "types/strref.h"

namespace UI
{

Combo::Combo(Surface&           surface,
             KeyProcessor&      keyProcessor,
             const Rectangle&   rect,
             Combo::DataSource& dataSource,
             std::size_t        selectedItem)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mX(rect.x)
    , mY(rect.y)
    , mWidth(rect.width)
    , mDataSource(dataSource)
    , mSelectedItem(selectedItem % mDataSource.getItemCount())
{
    mSurface.paintText(mX, mY, "<", 0xf, 0);
    mSurface.paintText(mX + mWidth - Surface::kFontWidth, mY, ">", 0xf, 0);

    DataSource::ItemText text;

    mDataSource.getItem(text, mSelectedItem);
    
    mSurface.paintTextC(mX + 20, mY, mWidth - 40, text, 0xf, 0);
}

bool Combo::create()
{
    mSurface.paintText(mX, mY, "<", 0, 0xf);
    mSurface.paintText(mX + mWidth - Surface::kFontWidth, mY, ">", 0, 0xf);
    paintSelection();
    mKeyProcessor.untilIdle();
    
    AutoRepeat autoRepeat;
    bool entered(false);
    
    while (1)
    {
        mKeyProcessor.poll(autoRepeat);

        auto keyId(autoRepeat.activeKey());

        if (Keys::cancel(keyId))
        {
            entered = false;
            break;
        }
        
        if (Keys::ok(keyId))
        {
            entered = true;
            break;
        }
        
        if (Keys::left(keyId))
        {
            mSelectedItem += mDataSource.getItemCount() - 1;
            mSelectedItem %= mDataSource.getItemCount();
            paintSelection();
        }
        
        if (Keys::right(keyId))
        {
            ++mSelectedItem %= mDataSource.getItemCount();
            paintSelection();
        }
    }

    return entered;
}

void Combo::paintSelection()
{
    DataSource::ItemText text;

    mDataSource.getItem(text, mSelectedItem);
    
    mSurface.paintTextC(mX + Surface::kFontWidth, mY, mWidth - (Surface::kFontWidth * 2), text, 0, 0xf);
}

}
