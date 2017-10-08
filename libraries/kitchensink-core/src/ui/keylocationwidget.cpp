#include "ui/keylocationwidget.h"

#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"
#include "ui/keys.h"
#include "keysource.h"
#include "types/stroutstream.h"

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
            StrOutStream os(mLocationStr);
            
            os.reset();
            os.appendChar('(');
            os.appendInt(location.row);
            os.appendStr(", ");
            os.appendInt(location.column);
            os.appendChar(')');

            locationSelected.fireAction();
            mLocationSet = true;
            mTrigger = false;
        }

        invalidateWidget();
    }
    else if (Keys::ok(event))
    {
        mTrigger = true;
        mLocationStr = "Waiting";
        invalidateWidget();
    }
    else
    {
        return false;
    }

    return mTrigger;
}

void KeyLocationWidget::setFocused(bool focused)
{
    mFocused = focused;
    mFlash = false;
}

void KeyLocationWidget::render(const RasterLine& rasterLine,
                               int               row)
{
    auto fg(mFocused ? Colors::kFocused : Colors::kUnfocused);
    auto bg(Colors::kBlack);

    if (mFocused && mTrigger && mFlash)
    {
        std::swap(fg, bg);
    }

    RenderUtil::text(mLocationStr, 0, row, rasterLine, fg, bg);
}

Dimension KeyLocationWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}

void KeyLocationWidget::clear()
{
    mLocationStr = "Waiting";
}
