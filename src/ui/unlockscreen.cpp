#include "ui/unlockscreen.h"

#include "event/screenevent.h"
#include "keyboardstateutil.h"

UnlockScreen::UnlockScreen(SecureMacroSet& secureMacroSet,
                           Timer&          timer,
                           EventStage&     next)
    : mSecureMacroSet(secureMacroSet)
    , mPasswordEntry("Password",
                     60,
                     PasswordEntryWidget(timer))
    , mStatusLabel("", Justify::kCenter)
    , mItems({{ mPasswordEntry,
                HStackWidget::Element(),
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
    StrRef password(mPasswordEntry.widget.password);
    
    if (!password.empty())
    {
        mStatusLabel.text = "Unlocking";
        mStatusLabel.invalidateWidget();

        if (KeyboardStateUtil::load(mSecureMacroSet, password))
        {
            mSecureMacroSet.password = password;
            screenCompleted.fireAction();
        }
        else
        {
            mPasswordEntry.widget.password = "";
            mStatusLabel.text = "Failed to unlock";
            mPasswordEntry.invalidateWidget();
            mStatusLabel.invalidateWidget();
        }
    }
}
