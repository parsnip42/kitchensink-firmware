#ifndef INCLUDED_SAVESECURESCREEN_H
#define INCLUDED_SAVESECURESCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelwidget.h"
#include "ui/screen.h"
#include "macroset.h"

class Timer;

class SaveSecureScreen : public Screen
{
public:
    SaveSecureScreen(SecureMacroSet& secureMacroSet,
                     EventStage&     next);
    
public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    SecureMacroSet&        mSecureMacroSet;
    LabelWidget            mStatusLabel;
    HStackWidget::Items<1> mItems;
    HStackWidget           mHStackWidget;
    EventStage&            mNext;
};

#endif
