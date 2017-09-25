#include "ui/unlockscreen.h"

#include "event/screenevent.h"
#include "keyboardstateutil.h"

UnlockScreen::UnlockScreen(SecureMacroSet& secureMacroSet,
                           Timer&          timer,
                           EventStage&     next)
    : mSecureMacroSet(secureMacroSet)
    , mPasswordEntry("Password",
                     70,
                     PasswordEntryWidget(timer))
    , mStatusLabel("", Justify::kCenter)
    , mItems({{ mPasswordEntry,
                mStatusLabel }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{
    mPasswordEntry.widget.applied = Action::memFn<UnlockScreen,
                                                  &UnlockScreen::onUnlock>(this);
}

bool UnlockScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& UnlockScreen::rootWidget()
{
    return mHStackWidget;
}

void UnlockScreen::onUnlock()
{
    mStatusLabel.text = "Unlocking..";
    mStatusLabel.invalidateWidget();

    if (KeyboardStateUtil::load(mSecureMacroSet,
                                mPasswordEntry.widget.password))
    {
        mNext.processEvent(ScreenEvent::create(ScreenEvent::Type::kHome, 0));
    }
    else
    {
        mStatusLabel.text = "Failed to unlock";
        mStatusLabel.invalidateWidget();
    }
}
