#include "actionprocessor.h"
#include "ctrlutil.h"
#include "eventqueue.h"
#include "keyboardstate.h"
#include "menudefinitions.h"
#include "ui/menu.h"
#include "ui/text.h"
#include "ui/textentry.h"

ActionProcessor::ActionProcessor(KeyProcessor&  keyProcessor,
                                 KeyboardState& keyboardState,
                                 UI::Surface&   surface)
    : mKeyProcessor(keyProcessor)
    , mKeyboardState(keyboardState)
    , mSurface(surface)
    , mMenuDefinitions(keyboardState)
{ }

bool ActionProcessor::processEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);
    
    if (event.pressed && (keyId.type() == KeyId::Type::kAction))
    {
        switch (keyId.actionType())
        {
        case KeyId::ActionType::kBuiltIn:
            fireBuiltIn(event.keyId.value(),
                        event);
            break;
            
        case KeyId::ActionType::kMenu:
            fireMenu(event.keyId.value(),
                     event);
            break;
        }
        
        return true;
    }

    return false;
}

void ActionProcessor::fireBuiltIn(int             action,
                                  const KeyEvent& event) const
{
    switch (action)
    {
    case 0:
    {
        CtrlUtil::bootloader();
        break;
    }
    
    case 1:
    {
        UI::Text text(mSurface);

        Types::StrBuf<20> line("Free Memory: ");

        line.appendInt(static_cast<int>(CtrlUtil::freeMemory()));
        
        text.appendLine(line);
        mKeyProcessor.untilKeyPress();
        mSurface.clear();
        break;
    }
    
    case 2:
    {
        UI::TextEntry entry(mSurface,
                            mKeyProcessor);

        if (entry.create(" Rename Layout #1 ",
                         mKeyboardState.layerStack[1].name))
        {
            mKeyboardState.layerStack[1].name = entry.text();
        }
        
        break;
    }
    }
}

void ActionProcessor::fireMenu(int             action,
                               const KeyEvent& event) const
{
    UI::Menu menu(mSurface);

    menu.createMenu(mMenuDefinitions.getDataSource(action),
                    mKeyProcessor);
}

void ActionProcessor::fireEdit() const
{
    UI::TextEntry foo(mSurface, mKeyProcessor);

    foo.create(" Rename Layout #0 ");
}
