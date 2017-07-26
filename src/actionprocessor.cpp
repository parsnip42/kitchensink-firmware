#include "actionprocessor.h"
#include "ctrlutil.h"
#include "keyboardstate.h"
#include "keylocation.h"

#include "types/strbuf.h"
#include "types/strostream.h"



ActionProcessor::ActionProcessor(KeyboardState& keyboardState,
                                 KeyEventStage& next)
    : mKeyboardState(keyboardState)
    , mNext(next)
{ }

void ActionProcessor::processKeyEvent(const KeyEvent& event)
{
    const auto& keyId(event.keyId);
    
    if (keyId.type() == KeyId::Type::kAction && !event.pressed)
    {
        switch (keyId.actionType())
        {
        case KeyId::ActionType::kBuiltIn:
            fireBuiltIn(event.keyId.value(), event);
            break;
            
        default:
            mNext.processKeyEvent(event);
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
        CtrlUtil::bootloader();
        break;
        
    default:
        break;
    }
    
    // case 1:
    // {
    //     if (event.pressed)
    //     {            
    //         UI::Text text(mSurface);

    //         {
    //             StrBuf<32> line;
    //             StrOStream ostream(line);
                
    //             ostream.appendStr("Free Memory: ")
    //                    .appendInt(static_cast<int>(CtrlUtil::freeMemory()));
            
    //             text.appendLine(line);
    //         }

    //         {
    //             text.appendLine("Running Benchmark..");

    //             auto start(millis());
    //             for (int i(0); i < 1000; ++i)
    //             {
    //                 mKeyProcessor.poll();
    //             }
    //             auto end(millis());

    //             {
    //                 StrBuf<32> line;
    //                 StrOStream ostream(line);

    //                 ostream.appendStr("  1000 polls: ")
    //                        .appendInt(static_cast<int>(end-start))
    //                        .appendStr("ms");

    //                 text.appendLine(line);
    //             }

    //             {
    //                 StrBuf<32> line;
    //                 StrOStream ostream(line);

    //                 ostream.appendStr("  ")
    //                        .appendInt(static_cast<int>(1000000 / (end-start)))
    //                        .appendStr(" polls/s");

    //                 text.appendLine(line);
    //             }

    //         }

    //         mKeyProcessor.untilKeyPress();
    //         mSurface.clear();
    //     }
    //     break;
    // }
    
    // case 2:
    // {
    //     break;
    // }
    // }
}

