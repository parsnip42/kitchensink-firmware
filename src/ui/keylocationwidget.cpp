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
    , mTrigger(false)
{
    mFlashTimer.scheduleRepeating(250, 250);
}

bool KeyLocationWidget::processEvent(const Event& event)
{
    if (mFlashTimer.matches(event))
    {
        mFlash = !mFlash;

        if (mTrigger && mKeySource.readKeyLocation(location))
        {
            StrOStream os(mLocationStr);
            
            os.reset();
            os.appendChar('(');
            os.appendInt(location.row);
            os.appendStr(", ");
            os.appendInt(location.column);
            os.appendChar(')');

            mLocationSet = true;
            mTrigger = false;
        }
    }

    invalidateWidget();

    return true;
}

void KeyLocationWidget::setFocused(bool focused)
{
    mFocused = focused;
    mFlash = false;

    if (focused)
    {
        mTrigger = true;
        mLocationStr = "Waiting";
    }
}

void KeyLocationWidget::render(const RasterLine& rasterLine,
                               int               row)
{
    auto fg(Colors::kWhite);
    auto bg(Colors::kBlack);

    if (mFocused && mFlash)
    {
        std::swap(fg, bg);
    }

    RenderUtil::text(mLocationStr, 0, row, rasterLine, fg, bg);
}

Dimension KeyLocationWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}
