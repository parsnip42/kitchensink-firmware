#include "screenmanager.h"

#include "autorepeat.h"
#include "keyboardstate.h"
#include "menudefinitions.h"
#include "ui/hsplitwidget.h"
#include "ui/titlewidget.h"
#include "ui/menuscreen.h"
#include "ui/editmacroscreen.h"
#include "ui/recordmacroscreen.h"
#include "ui/storagescreen.h"
#include "ui/benchmarkscreen.h"
#include "ui/keys.h"

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
    if (screenId.type == ScreenId::Type::kHome
        && !mScreenStack.empty())
    {
        mScreenStack.pop();
    }
    else if (mScreenStack.empty() || mScreenStack.top() != screenId)
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
        launchEditMacro(screenId.index);
        break;

    case ScreenId::Type::kRecordMacro:
    case ScreenId::Type::kRecordMacroRT:
        launchRecordMacro(screenId.index,
                          screenId.type == ScreenId::Type::kRecordMacroRT);
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

    TitleWidget titleWidget(mMenuDefinitions.getTitle(menuId));
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

void ScreenManager::launchEditMacro(int macroId)
{
    EditMacroScreen screen(mScreenStack,
                           mEventManager.timer,
                           mKeyboardState.macroSet,
                           macroId);
            
    OutputSink output(*this, screen);

    TitleWidget titleWidget("Edit Macro");
    HSplitWidget hSplit(titleWidget,       
                        screen.rootWidget(),
                        TitleWidget::kPreferredHeight);

    Surface::WidgetGuard guard(mSurface, hSplit);

    while (!mScreenStack.dirty())
    {
        mEventManager.poll(output);
    }

    // mEventManager.untilKeysReleased(output);
}

void ScreenManager::launchRecordMacro(int macroId, bool realtime)
{
    RecordMacroScreen screen(mScreenStack,
                             mEventManager.timer,
                             mKeyboardState.macroSet,
                             macroId,
                             realtime,
                             mEventManager.defaultOutput);

    OutputSink output(*this, screen);

    TitleWidget titleWidget("Recording Macro");
    HSplitWidget hSplit(titleWidget,       
                        screen.rootWidget(),
                        TitleWidget::kPreferredHeight);

    Surface::WidgetGuard guard(mSurface, hSplit);

    while (!mScreenStack.dirty())
    {
        mEventManager.poll(output);
    }
}
