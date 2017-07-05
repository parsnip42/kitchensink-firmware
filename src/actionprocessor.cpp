#include "actionprocessor.h"
#include "ctrlutil.h"
#include "eventqueue.h"
#include "keyboardstate.h"
#include "keylocation.h"
#include "menudefinitions.h"
#include "ui/surface.h"
#include "ui/menu.h"
#include "ui/text.h"
#include "ui/textentry.h"
#include "ui/combo.h"
#include "ui/recordmacro.h"
#include "types/strbuf.h"

#include <elapsedMillis.h>

namespace
{

class MacroTypeDataSource : public UI::Combo::DataSource
{
public:
    virtual void getItem(ItemText&   text,
                         std::size_t index) const
    {
        switch (index)
        {
        case 0:
            text = "Normal";
            break;
            
        case 1:
            text = "Realtime";
            break;
            
        case 2:
            text = "Key Combination";
            break;
        }
    }
    
    virtual std::size_t getItemCount() const
    {
        return 3;
    }
};

}

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

                StrBuf<20> title{{"Macro #"}};

                title.appendInt(macroIndex);
                
                mSurface.paintTextC(0, 0, 240, title, 0xf, 0);

                const auto& macroData(mKeyboardState.macroSet[macroIndex].data);
                
                UI::TextEntry entry(mSurface,
                                    mKeyProcessor,
                                    0,
                                    20,
                                    UI::Surface::kWidth,
                                    macroData.name);

                MacroTypeDataSource ds;
                
                UI::Combo combo(mSurface,
                                mKeyProcessor,
                                0,
                                45,
                                UI::Surface::kWidth,
                                ds,
                                0);
                
                if (entry.create())
                {
                    if (combo.create())
                    {
                        StrBuf<20> recordStr{{"Recording Macro #"}};
                        
                        recordStr.appendInt(macroIndex);
                        
                        UI::RecordMacro record(mSurface,
                                               mKeyProcessor,
                                               mUsbKeyboard);
                        
                        record.create(recordStr, (combo.selectedItem() == 1));
                        
                        const auto& macro(record.macro());

                        MacroType macroType((combo.selectedItem() == 2) ? MacroType::kInvert : MacroType::kSync);
                        
                        mKeyboardState.macroSet.setMacro(macroIndex,
                                                         macroType,
                                                         entry.text(),
                                                         macro.begin(),
                                                         macro.begin() + record.macroSize());
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
                StrBuf<32> line("Free Memory: ");
            
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
                    StrBuf<32> line("  1000 polls: ");
                
                    line.appendInt(static_cast<int>(end-start));
                    line.appendStr("ms");

                    text.appendLine(line);
                }

                {
                    StrBuf<32> line("  ");
                
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
        UI::Menu menu(mMenuDefinitions.getDataSource(action),
                      mSurface,
                      mKeyProcessor);
        
        menu.createMenu();
    }
}

void ActionProcessor::fireEdit() const
{
}
