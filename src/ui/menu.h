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
    Menu(const DataSource& dataSource,
         Surface&          surface,
         KeyEventBuffer&   buffer,
         KeyEventStage&    next);

public:
    void redraw();
    void poll();

    virtual void processKeyEvent(const KeyEvent& event) override;
    
private:
    void moveSelection(int selectionOffset);
    
    void paintMenu(int start,
                   int height);

    bool matchesFilter(const Item& item);
    
    void filteredItem(Item&       item,
                      std::size_t index);

    bool processExactFilterMatch();
    
    std::size_t filteredItemCount();
    
private:
    const DataSource& mDataSource;
    Surface&          mSurface;
    std::size_t       mSelected;
    StrBuf<12>        mFilter;
    VirtualKeyboard   mVKeyboard;
    bool              mQuit;
    KeyEventBuffer&   mBuffer;
    KeyEventStage&    mNext;
    
private:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};


inline
Menu::Menu(const DataSource& dataSource,
           Surface&          surface,
           KeyEventBuffer&   buffer,
           KeyEventStage&    next)
    : mDataSource(dataSource)
    , mSurface(surface)
    , mSelected(0)
    , mFilter()
    , mQuit(false)
    , mBuffer(buffer)
    , mNext(next)
{ }

}

#endif
