#include "ui/keylocationwidget.h"

#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"
#include "ui/keys.h"
#include "hardware/keyhardware.h"
#include "hardware/keyhardwareevent.h"
#include "hardware/keyhardwareeventhandler.h"
#include "hardware/ctrlutil.h"
#include "types/stroutstream.h"

KeyLocationWidget::KeyLocationWidget(TimerManager& timerManager,
                                     KeyHardware&  keyHardware)
    : mKeyHardware(keyHardware)
    , mLocationStr("Waiting")
    , mFocused(true)
    , mFlash(false)
    , mTrigger(false)
{ }

bool KeyLocationWidget::processEvent(const Event& event)
{
    if (Keys::ok(event))
    {
        // We want key release of ok to be fired as a result of an initial press
        // when our widget's focused (ie not the previous), so mark that here.
        mTrigger = true;
    }
    else if (Keys::okReleased(event) && mTrigger)
    {        
        mTrigger = false;
        readNextKeyPress();
    }
    else
    {
        return false;
    }

    return true;
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

    if (mFocused && !mFlash)
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

void KeyLocationWidget::readNextKeyPress()
{
    mLocationStr = "Waiting";
    invalidateWidget();

    do
    {
        auto now(CtrlUtil::nowMs());
            
        auto flash((now / 250) & 1);
                                      
        if (flash != mFlash)
        {
            invalidateWidget();
            mFlash = flash;
        }
            
        mLocationSet = false;
        mKeyHardware.poll(now,
                          KeyHardwareEventHandler::create([&](const KeyHardwareEvent& event)
        {
            if (event.pressed)
            {
                mLocationSet    = true;
                location.row    = event.row;
                location.column = event.column;
                
                
                StrOutStream os(mLocationStr);
                
                os.reset();
                os.appendChar('(');
                os.appendInt(location.row);
                os.appendStr(", ");
                os.appendInt(location.column);
                os.appendChar(')');
            }
        }));
    }
    while (!mLocationSet);

    mFlash = false;
        
    invalidateWidget();
    locationSelected.fireAction();
}
