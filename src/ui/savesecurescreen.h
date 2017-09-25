#ifndef INCLUDED_SAVESECURESCREEN_H
#define INCLUDED_SAVESECURESCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelwidget.h"
#include "ui/screen.h"
#include "macroset.h"

class EntropyPool;
class Timer;

class SaveSecureScreen : public Screen
{
public:
    SaveSecureScreen(SecureMacroSet& secureMacroSet,
                     EntropyPool&    entropyPool,
                     EventStage&     next);
    
public:
    virtual void screenInit() override;
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    SecureMacroSet& mSecureMacroSet;
    EntropyPool&    mEntropyPool;
    LabelWidget     mStatusLabel;
    EventStage&     mNext;
};

#endif
