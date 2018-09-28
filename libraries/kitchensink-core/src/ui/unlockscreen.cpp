#include "ui/unlockscreen.h"

#include "event/screenevent.h"
#include "keyboardstateutil.h"

#include "hardware/ctrlutil.h"

#include <stdio.h>
#include <string.h>

UnlockScreen::UnlockScreen(SecureMacroSet& secureMacroSet,
                           TimerManager&   timer,
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
    mHStackWidget.applied = Action::memFn<UnlockScreen,
                                          &UnlockScreen::onUnlock>(this);

    auto fm = CtrlUtil::freeMemory();

    char foo[24];
    snprintf(foo, sizeof(foo), "> %d : %d : %p", fm, sizeof(UnlockScreen), this);
    mStatusLabel.text = foo;
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

        if (KeyboardStateUtil::load(mSecureMacroSet, password) == KeyboardStateUtil::StorageResult::OK)
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
