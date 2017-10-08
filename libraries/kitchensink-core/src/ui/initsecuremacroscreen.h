#ifndef INCLUDED_INITSECUREMACROSCREEN_H
#define INCLUDED_INITSECUREMACROSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/labelwidget.h"
#include "ui/buttonwidget.h"
#include "ui/screen.h"
#include "ui/passwordentrywidget.h"
#include "macroset.h"

class Timer;

class InitSecureMacroScreen : public Screen
{
public:
    InitSecureMacroScreen(SecureMacroSet& secureMacroSet,
                          TimerManager&          timer,
                          EventStage&     next);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    void onApply();
    
private:
    SecureMacroSet&                     mSecureMacroSet;
    Timer                       mFlashTimer;
    LabelledWidget<PasswordEntryWidget> mPasswordEntry;
    LabelledWidget<PasswordEntryWidget> mConfirmEntry;
    LabelWidget                         mStatusLabel;
    HStackWidget::Items<3>              mItems;
    HStackWidget                        mHStackWidget;
    EventStage&                         mNext;
};

#endif
