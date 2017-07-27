#ifndef INCLUDED_UI_MENU_H
#define INCLUDED_UI_MENU_H

#include "keyid.h"
#include "keyeventstage.h"
#include "keyeventbuffer.h"
#include "keyprocessor.h"
#include "types/strbuf.h"
#include "types/strostream.h"
#include "types/strref.h"
#include "ui/surface.h"
#include "virtualkeyboard.h"
#include "eventmanager.h"

#include <cstdint>

class KeyProcessor;

namespace UI
{

class Menu : public KeyEventStage
{
public:
    class Item
    {
    public:
        StrBuf<24> title;
        StrBuf<12> shortcut;
        KeyId      keyId;
    };
    
public:
    class DataSource
    {
    public:
        virtual void getItem(Item&       menuItem,
                             std::size_t index) const = 0;
        
        virtual std::size_t getItemCount() const = 0;
    };

public:
    Menu(const StrRef&     title,
         const DataSource& dataSource,
         Surface&          surface,
         EventManager&     eventManager);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    void poll();
    
private:
    void redraw();
    
    void moveSelection(int selectionOffset);
    
    void paintMenu(int start,
                   int height);

    bool matchesFilter(const Item& item);
    
    void filteredItem(Item&       item,
                      std::size_t index);

    bool processExactFilterMatch();
    
    std::size_t filteredItemCount();
    
private:
    StrRef            mTitle;
    const DataSource& mDataSource;
    Surface&          mSurface;
    std::size_t       mSelected;
    StrBuf<12>        mFilter;
    VirtualKeyboard   mVKeyboard;
    bool              mQuit;
    EventManager&     mEventManager;
    
private:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};


inline
Menu::Menu(const StrRef&     title,
           const DataSource& dataSource,
           Surface&          surface,
           EventManager&     eventManager)
    : mTitle(title)
    , mDataSource(dataSource)
    , mSurface(surface)
    , mSelected(0)
    , mFilter()
    , mQuit(false)
    , mEventManager(eventManager)
{ }

}

#endif
