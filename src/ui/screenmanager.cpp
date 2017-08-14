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
#include "ui/keyconfigscreen.h"
#include "ui/keys.h"
#include "ui/homescreen.h"
#include "types/strostream.h"

namespace
{

class OutputSink : public EventStage
{
public:
    OutputSink(ScreenManager& screenManager,
               EventStage&    next)
        : mScreenManager(screenManager)
        , mNext(next)
    { }

public:
    virtual void processEvent(const Event& event) override
    {
        if (event.is<ScreenEvent>())
        {
            auto screenEvent(event.get<ScreenEvent>());
            
            mScreenManager.pushScreen(ScreenId(screenEvent.type,
                                               screenEvent.index));
        }
        else if (Keys::cancel(event))
        {
            mScreenManager.popScreen();
        }
        
        mNext.processEvent(event);
    }

private:
    ScreenManager& mScreenManager;
    EventStage& mNext;
};

}

ScreenManager::ScreenManager(Surface&       surface,
                             EventManager&  eventManager,
                             KeyboardState& keyboardState,
                             HomeScreen&    homeScreen)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mKeyboardState(keyboardState)
    , mHomeScreen(homeScreen)
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

void ScreenManager::poll(EventStage& next)
{
    while (true)
    {
        flush();
        
        if (mScreenStack.empty())
        {
            OutputSink output(*this, mHomeScreen);
            
            Surface::WidgetGuard guard(mSurface,
                                       mHomeScreen.rootWidget());

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
        break;
        
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
    MenuScreen screen(mMenuDefinitions.getDataSource(menuId),
                      mScreenStack,
                      mEventManager);
            
    AutoRepeat autoRepeat(mEventManager.timer,
                          screen);
    
    displayScreen(autoRepeat, screen.rootWidget());
}

void ScreenManager::launchScreen(int screenId)
{
    switch (screenId)
    {
    case 0:
    {
        StorageScreen screen;

        displayScreen(screen,
                      screen.rootWidget());
        break;
    }
            
    case 1:
    {
        BenchmarkScreen screen(mEventManager);

        displayScreen(screen,
                      screen.rootWidget());
        break;
    }

    case 2:
    {
        KeyConfigScreen screen;

        displayScreen(screen,
                      screen.rootWidget());
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

    displayScreen(screen, screen.rootWidget());
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
    
    displayScreen(screen, screen.rootWidget());
}

void ScreenManager::displayScreen(EventStage& stage,
                                  Widget&        content)
{
    OutputSink output(*this, stage);

    TitleWidget titleWidget;

    createTitlePath(titleWidget.text);

    HSplitWidget hSplit(titleWidget,       
                        content,
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

    case ScreenId::Type::kScreen:
        switch (screenId.index)
        {
        case 0:
            os.appendStr("Storage");
            break;
            
        case 1:
            os.appendStr("Benchmark");
            break;

        case 2:
            os.appendStr("Layout Configuration");
            break;
        }
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
