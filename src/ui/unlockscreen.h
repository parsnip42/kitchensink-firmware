#ifndef INCLUDED_UNLOCKSCREEN_H
#define INCLUDED_UNLOCKSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/labelwidget.h"
#include "ui/buttonwidget.h"
#include "ui/screen.h"
#include "ui/passwordentrywidget.h"
#include "macroset.h"

class Timer;

class UnlockScreen : public Screen
{
public:
    UnlockScreen(SecureMacroSet& secureMacroSet,
                 Timer&          timer,
                 EventStage&     next);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    void onUnlock();
    
private:
    SecureMacroSet&                     mSecureMacroSet;
    LabelledWidget<PasswordEntryWidget> mPasswordEntry;
    ButtonWidget                        mUnlockButton;
    LabelWidget                         mStatusLabel;
    HStackWidget::Items<3>              mItems;
    HStackWidget                        mHStackWidget;
    EventStage&                         mNext;
};

#endif
