#include "ui/savesecurescreen.h"

#include "event/screenevent.h"
#include "keyboardstateutil.h"

SaveSecureScreen::SaveSecureScreen(SecureMacroSet& secureMacroSet,
                                   EventStage&     next)
    : mSecureMacroSet(secureMacroSet)
    , mStatusLabel("", Justify::kCenter)
    , mItems({{ mStatusLabel }})
    , mHStackWidget(mItems, true)
    , mNext(next)
{ }

bool SaveSecureScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& SaveSecureScreen::rootWidget()
{
    return mHStackWidget;
}
