#include "ui/homeledwidget.h"

#include "data/keycode.h"
#include "ui/colors.h"
#include "ui/font.h"
#include "ui/renderutil.h"
#include "ui/keys.h"
#include "serialize/eventserializer.h"
#include "event/smartevent.h"

HomeLedWidget::HomeLedWidget(const SmartKeySet& smartKeySet,
                             Timer&             timer)
    : mSmartKeySet(smartKeySet)
    , mFlashTimer(timer.createHandle())
    , mFocused(true)
    , mFlash(true)
    , mTrigger(false)
{
    mFlashTimer.scheduleRepeating(250, 250);
}

bool HomeLedWidget::processEvent(const Event& inEvent)
{
    if (mFlashTimer.matches(inEvent))
    {
        mFlash = !mFlash;
        invalidateWidget();

        return true;
    }
    else if (Keys::ok(inEvent))
    {
        if (mTrigger)
        {
            homeLed = HomeLed();
        }
        
        mTrigger = !mTrigger;
        invalidateWidget();

        return true;
    }
    else if (Keys::cancel(inEvent) && mTrigger)
    {
        mTrigger = false;
        invalidateWidget();

        return true;
    }
    else if (mTrigger && !inEvent.inverted())
    {
        if (inEvent.is<KeyEvent>())
        {
            auto keyEvent(inEvent.get<KeyEvent>());

            switch (keyEvent.key)
            {
            case KeyCode::NumLock:
                homeLed.type  = HomeLed::Type::kKeyboard;
                homeLed.index = HomeLed::kNumLock;
                mTrigger = false;
                invalidateWidget();
                break;
                
            case KeyCode::CapsLock:
                homeLed.type  = HomeLed::Type::kKeyboard;
                homeLed.index = HomeLed::kCapsLock;
                mTrigger = false;
                invalidateWidget();
                break;

            case KeyCode::ScrollLock:
                homeLed.type  = HomeLed::Type::kKeyboard;
                homeLed.index = HomeLed::kScrollLock;
                mTrigger = false;
                invalidateWidget();
                break;

            default:
                break;
            }

            return true;
        }
        else if (inEvent.is<SmartEvent>())
        {
            auto smartEvent(inEvent.get<SmartEvent>());
            
            homeLed.type  = HomeLed::Type::kSmartKey;
            homeLed.index = smartEvent.smartId;
            mTrigger = false;

            invalidateWidget();
            
            return true;
        }
    }
    
    return false;
}

void HomeLedWidget::setFocused(bool focused)
{
    mFocused = focused;
    mFlash   = false;

    if (!mFocused)
    {
        mTrigger = false;
    }
}

void HomeLedWidget::render(const RasterLine& rasterLine,
                           int               row)
{
    auto fg(mFocused ? Colors::kFocused : Colors::kUnfocused);
    auto bg(Colors::kBlack);

    if (mFocused && mTrigger && mFlash)
    {
        std::swap(fg, bg);
    }

    RenderUtil::text(homeLed.text(mSmartKeySet), 0, row, rasterLine, fg, bg);
}

Dimension HomeLedWidget::minimumSize() const
{
    return Dimension(0, Font::kHeight);
}

void HomeLedWidget::update()
{
    invalidateWidget();
}
