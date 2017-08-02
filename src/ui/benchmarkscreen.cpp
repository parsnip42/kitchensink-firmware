#include "ui/benchmarkscreen.h"

#include "keyevent.h"
#include "eventmanager.h"
#include "ui/surface.h"

#include "types/strbuf.h"
#include "types/strostream.h"
#include "ctrlutil.h"

#include <elapsedMillis.h>

namespace
{

class NullKeyStage : public KeyEventStage
{
public:
    virtual void processKeyEvent(const KeyEvent& event) override
    {
        
    }
};

}

BenchmarkScreen::BenchmarkScreen(Surface&      surface,
                                 EventManager& eventManager)
    : mEventManager(eventManager)
    , mSurface(surface)
    , mTextScreen(surface)
    , mQuit(false)
{ }

void BenchmarkScreen::processKeyEvent(const KeyEvent& event)
{
    if (event.pressed)
    {
        mQuit = true;
    }
}

void BenchmarkScreen::poll()
{
    mTextScreen.init();
    
    {
        StrBuf<32> line;
        StrOStream ostream(line);
                
        ostream.appendStr("Free Memory: ")
               .appendInt(static_cast<int>(CtrlUtil::freeMemory()));
            
        mTextScreen.appendLine(line);
    }

    mTextScreen.appendLine("Running Benchmark..");

    auto start(millis());

    NullKeyStage nullNext;
    
    for (int i(0); i < 1000; ++i)
    {
        mEventManager.poll(nullNext);
    }
    
    auto end(millis());

    {
        StrBuf<64> line;
        StrOStream ostream(line);

        ostream.appendStr("  1000 polls: ")
               .appendInt(static_cast<int>(end-start))
               .appendStr("ms (")
               .appendInt(static_cast<int>(1000000 / (end-start)))
               .appendStr(" polls/s)");

        mTextScreen.appendLine(line);
    }
        
    while (!mQuit)
    {
        mEventManager.poll(*this);
    }
}
