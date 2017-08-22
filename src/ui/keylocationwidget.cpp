#include "ui/keylocationwidget.h"

#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"
#include "keysource.h"

KeyLocationWidget::KeyLocationWidget(Timer&     timer,
                                     KeySource& keySource)
    : mKeySource(keySource)
    , mFlashTimer(timer.createHandle())
    , mLocationStr("Waiting")
    , mFocused(true)
    , mFlash(true)
{
    mFlashTimer.scheduleRepeating(250, 250);
}

void KeyLocationWidget::processEvent(const Event& event)
{
    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;

        if (mKeySource.readKeyLocation(location))
        {
            StrOStream os(mLocationStr);
            
            os.reset();
            
            os.appendChar('(');
            os.appendInt(location.row);
            os.appendStr(", ");
            os.appendInt(location.column);
            os.appendChar(')');

            mLocationSet = true;
        }
    }

    invalidateWidget();
}

void KeyLocationWidget::setFocused(bool focused)
{
    mFocused = focused;
    mFlash = false;
}

void KeyLocationWidget::render(const RasterLine& rasterLine, int row)
{
    auto fg(mFocused ? Colors::kBlack : Colors::kWhite);
    auto bg(mFocused ? Colors::kWhite : Colors::kBlack);

    if (mFlash)
    {
        std::swap(fg, bg);
    }

    RenderUtil::text(mLocationStr, 0, row, rasterLine, fg, bg);
}

Dimension KeyLocationWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}
