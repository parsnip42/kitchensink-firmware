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
#include "ui/label.h"
#include "ui/combo.h"
#include "ui/recordmacro.h"
#include "ui/tablelayout.h"

#include "types/strbuf.h"
#include "types/strostream.h"



#include "serialize/serializer.h"
#include "storage/storage.h"




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
                                 UI::Surface&   surface,
                                 KeyEventStage& next)
    : mKeyProcessor(keyProcessor)
    , mUsbKeyboard(usbKeyboard)
    , mKeyboardState(keyboardState)
    , mSurface(surface)
    , mMenuDefinitions(keyboardState)
    , mNext(next)
{ }

void ActionProcessor::processKeyEvent(const KeyEvent& event)
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

                auto& macro(mKeyboardState.macroSet[macroIndex]);

                UI::TableLayout layout(72, UI::Surface::kWidth, 20, 8);
                
                UI::Label(mSurface,
                          layout.next(),
                          "Name",
                          UI::Label::Justify::Right);

                UI::TextEntry titleEntry(mSurface,
                                         mKeyProcessor,
                                         layout.next(),
                                         macro.name);
                
                UI::Label(mSurface,
                          layout.next(),
                          "Shortcut",
                          UI::Label::Justify::Right);
                
                UI::TextEntry shortcutEntry(mSurface,
                                            mKeyProcessor,
                                            layout.next(),
                                            macro.shortcut);

                MacroTypeDataSource ds;
                
                UI::Label(mSurface,
                          layout.next(),
                          "Type",
                          UI::Label::Justify::Right);

                UI::Combo combo(mSurface,
                                mKeyProcessor,
                                layout.next(),
                                ds,
                                0);
                
                if (titleEntry.focus() &&
                    shortcutEntry.focus())
                {
                    if (combo.create())
                    {
                        StrBuf<20> recordStr;
                        StrOStream ostream(recordStr);
                        
                        ostream.appendStr("Recording Macro #")
                               .appendInt(macroIndex);

                        
                        UI::RecordMacro record(mSurface,
                                               mKeyProcessor,
                                               mUsbKeyboard);
                        
                        MacroType macroType((combo.selectedItem() == 2) ? MacroType::kInvert : MacroType::kSync);

                        macro.type = macroType;
                        macro.name = titleEntry.text();
                        macro.shortcut = shortcutEntry.text();

                        record.create(recordStr,
                                      macro,
                                      (combo.selectedItem() == 1));
                        
                        Storage storage;
                        
                        {
                            Serializer<MacroSet> s;
                            
                            auto os(storage.write(Storage::Region::Macro));

                            s.serialize(mKeyboardState.macroSet, os);
                        }
                        

                    }
                }

                mSurface.clear();
            }
            break;
        }
    }
    else
    {
        mNext.processKeyEvent(event);
    }
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
                StrBuf<32> line;
                StrOStream ostream(line);
                
                ostream.appendStr("Free Memory: ")
                       .appendInt(static_cast<int>(CtrlUtil::freeMemory()));
            
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
                    StrBuf<32> line;
                    StrOStream ostream(line);

                    ostream.appendStr("  1000 polls: ")
                           .appendInt(static_cast<int>(end-start))
                           .appendStr("ms");

                    text.appendLine(line);
                }

                {
                    StrBuf<32> line;
                    StrOStream ostream(line);

                    ostream.appendStr("  ")
                           .appendInt(static_cast<int>(1000000 / (end-start)))
                           .appendStr(" polls/s");

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
