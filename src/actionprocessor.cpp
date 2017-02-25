#include "actionprocessor.h"
#include "ctrlutil.h"
#include "eventqueue.h"
#include "keyboardstate.h"
#include "menudefinitions.h"
#include "ui/menu.h"
#include "ui/text.h"
#include "ui/textentry.h"
#include "ui/recordmacro.h"
#include "types/strbuf.h"

#include <elapsedMillis.h>

ActionProcessor::ActionProcessor(KeyProcessor&  keyProcessor,
                                 UsbKeyboard&   usbKeyboard,
                                 KeyboardState& keyboardState,
                                 UI::Surface&   surface)
    : mKeyProcessor(keyProcessor)
    , mUsbKeyboard(usbKeyboard)
    , mKeyboardState(keyboardState)
    , mSurface(surface)
    , mMenuDefinitions(keyboardState)
{ }

bool ActionProcessor::processEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);
    
    if (keyId.type() == KeyId::Type::kAction)
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
        case KeyId::ActionType::kEditMacro:
            if (event.pressed)
            {
                auto macroIndex(keyId.value());

                mSurface.clear();

                Types::StrBuf<20> title{{"Rename Macro #"}};

                title.appendInt(macroIndex);
                
                mSurface.paintText(0, 0, title, 0xf, 0);

                UI::TextEntry entry(mSurface,
                                    mKeyProcessor,
                                    0,
                                    20,
                                    mKeyboardState.macroSet[macroIndex].data);
                
                if (entry.create())
                {
                    mKeyboardState.macroSet[macroIndex].data = entry.text();
                    
                    {
                        Types::StrBuf<20> recordStr{{"Recording Macro #"}};

                        recordStr.appendInt(macroIndex);
                        
                        UI::RecordMacro record(mSurface,
                                               mKeyProcessor,
                                               mUsbKeyboard);
                        
                        record.create(recordStr, false);
                        
                        const auto& macro(record.macro());
                        
                        mKeyboardState.macroSet.setMacro(macroIndex, macro.rbegin(), macro.rend());
                    }
                }

                mSurface.clear();
            }
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
        if (event.pressed)
        {
            UI::Text text(mSurface);

            {
                Types::StrBuf<32> line("Free Memory: ");
            
                line.appendInt(static_cast<int>(CtrlUtil::freeMemory()));
            
                text.appendLine(line);
            }

            {
                text.appendLine("Running Benchmark..");

                auto start(millis());
                for (int i(0); i < 1000; ++i)
                {
                    mKeyProcessor.poll();
                }
                auto end(millis());

                {
                    Types::StrBuf<32> line("  1000 polls: ");
                
                    line.appendInt(static_cast<int>(end-start));
                    line.appendStr("ms");

                    text.appendLine(line);
                }

                {
                    Types::StrBuf<32> line("  ");
                
                    line.appendInt(static_cast<int>(1000000 / (end-start)));
                    line.appendStr(" polls/s");

                    text.appendLine(line);
                }

            }

            mKeyProcessor.untilKeyPress();
            mSurface.clear();

        }
        break;
    }
    
    case 2:
    {
        break;
    }
    }
}

void ActionProcessor::fireMenu(int             action,
                               const KeyEvent& event) const
{
    if (event.pressed)
    {
        UI::Menu menu(mSurface);
        
        menu.createMenu(mMenuDefinitions.getDataSource(action),
                        mKeyProcessor);
    }
}

void ActionProcessor::fireEdit() const
{
}
