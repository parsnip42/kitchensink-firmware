#include "screenmanager.h"

#include "autorepeat.h"
#include "keyboardstate.h"
#include "menudefinitions.h"
#include "ui/menuscreen.h"
#include "ui/editmacroscreen.h"
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

void ScreenManager::launch(const ScreenId& screen)
{
    switch (screen.type)
    {

    case ScreenId::Type::kHome:
        launchMenu(0);
        break;
        
    case ScreenId::Type::kMenu:
        launchMenu(screen.index);
        break;

    case ScreenId::Type::kScreen:
        launchScreen(screen.index);
        break;

    case ScreenId::Type::kEditMacro:
        launchEditMacro(screen.index);
        break;
        
    }
}

void ScreenManager::launchMenu(int menuId)
{
    MenuScreen menu(mMenuDefinitions.getTitle(menuId),
                    mMenuDefinitions.getDataSource(menuId),
                    mScreenStack,
                    mEventManager.timer,
                    mEventManager);
            
    AutoRepeat autoRepeat(mEventManager.timer,
                          menu);
    
    OutputSink output(*this, autoRepeat);
    
    Surface::WidgetGuard guard(mSurface, menu.rootWidget());

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
    auto& macro(mKeyboardState.macroSet[macroId]);

    EditMacroScreen screen(mEventManager.timer,
                           mKeyboardState.macroSet,
                           macro);
            
    OutputSink output(*this, screen);
            
    Surface::WidgetGuard guard(mSurface, screen.rootWidget());

    while (!mScreenStack.dirty())
    {
        mEventManager.poll(output);
    }

    // mEventManager.untilKeysReleased(output);
}
