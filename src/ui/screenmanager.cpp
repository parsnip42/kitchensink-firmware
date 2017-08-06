#include "screenmanager.h"

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

        if (keyId.type() == KeyId::Type::kAction && event.pressed)
        {
            mScreenManager.pushScreen(ScreenId(ScreenId::Type(keyId.actionType()),
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

void ScreenManager::pushScreen(const ScreenId& screen)
{
    if (mScreenStack.empty() || mScreenStack.top() != screen)
    {
        mScreenStack.push(screen);
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
            
    case ScreenId::Type::kMenu:
    {
        MenuScreen menu(mMenuDefinitions.getTitle(screen.index),
                        mMenuDefinitions.getDataSource(screen.index),
                        mScreenStack,
                        mEventManager.timer,
                        mEventManager);
            
        OutputSink output(*this, menu);
            
        Surface::WidgetGuard guard(mSurface, menu.rootWidget());

        while (!mScreenStack.dirty())
        {
            mEventManager.poll(output);
        }
            
        break;
    }

    case ScreenId::Type::kScreen:
    {
        switch (screen.index)
        {
        case 0:
        {
            StorageScreen storage(mSurface,
                                  mEventManager);
                
            storage.poll();
            break;
        }
            
        case 1:
        {
            BenchmarkScreen benchmark(mSurface,
                                      mEventManager);
                
            benchmark.poll();
            break;
        }
            
        default:
            break;
        }

        break;
    }

    case ScreenId::Type::kEditMacro:
    {
        auto& macro(mKeyboardState.macroSet[screen.index]);

        EditMacroScreen screen(mSurface,
                               mEventManager,
                               mKeyboardState.macroSet,
                               macro);
            
        OutputSink output(*this, screen);
            
        Surface::WidgetGuard guard(mSurface, screen.rootWidget());

        while (!mScreenStack.dirty())
        {
            mEventManager.poll(output);
        }
            
        break;
    }
        
    }
}
