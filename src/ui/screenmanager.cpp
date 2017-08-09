#include "screenmanager.h"

#include "autorepeat.h"
#include "keyboardstate.h"
#include "ui/menudefinitions.h"
#include "ui/hsplitwidget.h"
#include "ui/titlewidget.h"
#include "ui/menuscreen.h"
#include "ui/editmacroscreen.h"
#include "ui/recordmacroscreen.h"
#include "ui/storagescreen.h"
#include "ui/benchmarkscreen.h"
#include "ui/keys.h"
#include "types/strostream.h"

namespace
{

class OutputSink : public KeyEventStage
{
public:
    OutputSink(ScreenManager& screenManager,
               KeyEventStage& next)
        : mScreenManager(screenManager)
        , mNext(next)
    { }

public:
    virtual void processKeyEvent(const KeyEvent& event) override
    {
        auto keyId(event.keyId);

        if (keyId.type() == KeyId::Type::kScreen && event.pressed)
        {
            mScreenManager.pushScreen(ScreenId(ScreenId::Type(keyId.screenType()),
                                               keyId.value()));
        }
        else if (Keys::cancel(keyId) && event.pressed)
        {
            mScreenManager.popScreen();
        }
        
        mNext.processKeyEvent(event);
    }

private:
    ScreenManager& mScreenManager;
    KeyEventStage& mNext;
};

}

ScreenManager::ScreenManager(Surface&       surface,
                             EventManager&  eventManager,
                             KeyboardState& keyboardState)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mKeyboardState(keyboardState)
    , mMenuDefinitions(keyboardState)
{ }

void ScreenManager::pushScreen(const ScreenId& screenId)
{
    if (!mScreenStack.empty() &&
        (screenId.type == ScreenId::Type::kHome || mScreenStack.top() == screenId))
    {
        mScreenStack.pop();
    }
    else if (!mScreenStack.full())
    {
        mScreenStack.push(screenId);
    }
}

void ScreenManager::popScreen()
{
    if (!mScreenStack.empty())
    {
        mScreenStack.pop();
    }
}

void ScreenManager::poll(KeyEventStage& next)
{
    while (true)
    {
        flush();
        
        if (mScreenStack.empty())
        {
            OutputSink output(*this, next);

            mSurface.redraw();
            
            while (!mScreenStack.dirty())
            {
                mEventManager.poll(output);
            }
        }
        else
        {
            launch(mScreenStack.top());
        }
    }
}

void ScreenManager::launch(const ScreenId& screenId)
{
    switch (screenId.type)
    {
    case ScreenId::Type::kHome:
        launchMenu(0);
        break;
        
    case ScreenId::Type::kMenu:
        launchMenu(screenId.index);
        break;

    case ScreenId::Type::kScreen:
        launchScreen(screenId.index);
        break;

    case ScreenId::Type::kEditMacro:
        launchEditMacro(mKeyboardState.macroSet,
                        screenId.index);
        break;

    case ScreenId::Type::kRecordMacro:
    case ScreenId::Type::kRecordMacroRT:
        launchRecordMacro(mKeyboardState.macroSet,
                          screenId.index,
                          screenId.type == ScreenId::Type::kRecordMacroRT);

    case ScreenId::Type::kEditSMacro:
        launchEditMacro(mKeyboardState.secureMacroSet,
                        screenId.index);
        break;

    case ScreenId::Type::kRecordSMacro:
    case ScreenId::Type::kRecordSMacroRT:
        launchRecordMacro(mKeyboardState.secureMacroSet,
                          screenId.index,
                          screenId.type == ScreenId::Type::kRecordSMacroRT);

        break;
    }
}

void ScreenManager::launchMenu(int menuId)
{
    MenuScreen menu(mMenuDefinitions.getDataSource(menuId),
                    mScreenStack,
                    mEventManager);
            
    AutoRepeat autoRepeat(mEventManager.timer,
                          menu);
    
    OutputSink output(*this, autoRepeat);

    mEventManager.flush(output);

    TitleWidget titleWidget;

    createTitlePath(titleWidget.text);
    
    HSplitWidget hSplit(titleWidget,       
                        menu.rootWidget(),
                        TitleWidget::kPreferredHeight);
    
    Surface::WidgetGuard guard(mSurface, hSplit);

    while (!mScreenStack.dirty())
    {
        mEventManager.poll(output);
    }

}

void ScreenManager::launchScreen(int screenId)
{
    switch (screenId)
    {
    case 0:
    {
        StorageScreen storage;

        OutputSink output(*this, storage);
            
        Surface::WidgetGuard guard(mSurface, storage.rootWidget());
        
        while (!mScreenStack.dirty())
        {
            mEventManager.poll(output);
        }
        
        break;
    }
            
    case 1:
    {
        BenchmarkScreen benchmark(mEventManager);

        OutputSink output(*this, benchmark);
            
        Surface::WidgetGuard guard(mSurface, benchmark.rootWidget());

        benchmark.run();
        
        while (!mScreenStack.dirty())
        {
            mEventManager.poll(output);
        }

        break;
    }
            
    default:
        break;
    }
}

void ScreenManager::launchEditMacro(MacroSet& macroSet,
                                    int       macroId)
{
    EditMacroScreen screen(mScreenStack,
                           mEventManager.timer,
                           macroSet,
                           macroId);
            
    OutputSink output(*this, screen);

    TitleWidget titleWidget;

    createTitlePath(titleWidget.text);

    HSplitWidget hSplit(titleWidget,       
                        screen.rootWidget(),
                        TitleWidget::kPreferredHeight);

    Surface::WidgetGuard guard(mSurface, hSplit);

    while (!mScreenStack.dirty())
    {
        mEventManager.poll(output);
    }
}

void ScreenManager::launchRecordMacro(MacroSet& macroSet,
                                      int       macroId,
                                      bool      realtime)
{
    RecordMacroScreen screen(mScreenStack,
                             mEventManager.timer,
                             macroSet,
                             macroId,
                             realtime,
                             mEventManager.defaultOutput);

    OutputSink output(*this, screen);

    TitleWidget titleWidget;

    createTitlePath(titleWidget.text);

    HSplitWidget hSplit(titleWidget,       
                        screen.rootWidget(),
                        TitleWidget::kPreferredHeight);

    Surface::WidgetGuard guard(mSurface, hSplit);

    while (!mScreenStack.dirty())
    {
        mEventManager.poll(output);
    }
}

void ScreenManager::createTitlePath(const StrOStream& os)
{
    for (auto it(mScreenStack.begin()); it != mScreenStack.end(); ++it)
    {
        if (it != mScreenStack.begin())
        {
            os.appendStr(" : ");
        }
        
        createTitle(*it, os);
    }
}

void ScreenManager::createTitle(const ScreenId&   screenId,
                                const StrOStream& os)
{
    switch (screenId.type)
    {
    case ScreenId::Type::kHome:
    case ScreenId::Type::kMenu:
        os.appendStr(mMenuDefinitions.getTitle(screenId.index));
        break;
        
    case ScreenId::Type::kEditMacro:
        os.appendStr("Edit Macro");
        break;

    case ScreenId::Type::kRecordMacro:
    case ScreenId::Type::kRecordMacroRT:
        os.appendStr("Record Macro");
        break;
        
    case ScreenId::Type::kEditSMacro:
        os.appendStr("Edit Secure Macro");
        break;

    case ScreenId::Type::kRecordSMacro:
    case ScreenId::Type::kRecordSMacroRT:
        os.appendStr("Record Secure Macro");
        break;

    default:
        break;
    }
}

void ScreenManager::flush()
{
    OutputSink output(*this, mEventManager.defaultOutput);
    
    mEventManager.flush(output);
}
