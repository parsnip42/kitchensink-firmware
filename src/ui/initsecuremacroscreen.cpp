#include "ui/initsecuremacroscreen.h"

#include "event/screenevent.h"
#include "keyboardstateutil.h"
#include "config.h"

InitSecureMacroScreen::InitSecureMacroScreen(SecureMacroSet& secureMacroSet,
                                             Timer&          timer,
                                             EventStage&     next)
    : mSecureMacroSet(secureMacroSet)
    , mFlashTimer(timer.createHandle())
    , mPasswordEntry("Password",
                     60,
                     PasswordEntryWidget(timer))
    , mConfirmEntry("Confirm",
                    60,
                    PasswordEntryWidget(timer))
    , mStatusLabel("Existing data will be erased", Justify::kCenter)
    , mItems({{ mPasswordEntry,
                mConfirmEntry,
                mStatusLabel }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    mFlashTimer.scheduleRepeating(250, 250);

    mConfirmEntry.widget.applied = Action::memFn<InitSecureMacroScreen,
                                                 &InitSecureMacroScreen::onApply>(this);
}

bool InitSecureMacroScreen::processEvent(const Event& event)
{
    if (mFlashTimer.matches(event))
    {
        mStatusLabel.visible = !mStatusLabel.visible;
        mStatusLabel.invalidateWidget();
        return true;
    }
        
    return mHStackWidget.processEvent(event);
}

Widget& InitSecureMacroScreen::rootWidget()
{
    return mHStackWidget;
}

void InitSecureMacroScreen::onApply()
{
    StrRef passwordA(mPasswordEntry.widget.password);
    StrRef passwordB(mConfirmEntry.widget.password);

    if (!passwordA.empty() && !passwordB.empty())
    {
        mFlashTimer.cancel();
        mStatusLabel.visible = true;
        
        if (passwordA != passwordB)
        {
            mStatusLabel.text = "Passwords do not match";
            mStatusLabel.invalidateWidget();
        }
        else if (passwordA.length() < Config::kPasswordMin)
        {
            mStatusLabel.text = "Password too short";
            mStatusLabel.invalidateWidget();
        }
        else if (passwordA.length() > Config::kPasswordMax)
        {
            mStatusLabel.text = "Password too long";
            mStatusLabel.invalidateWidget();
        }
        else
        {
            mSecureMacroSet.lock();
            mSecureMacroSet.password = passwordA;
            
            mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kScreen,
                                                   ScreenEvent::kMacroSave));
        }
    }
}
