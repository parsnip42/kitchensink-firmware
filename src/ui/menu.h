#ifndef INCLUDED_UI_MENU_H
#define INCLUDED_UI_MENU_H

#include "keyid.h"
#include "keyprocessor.h"
#include "types/strbuf.h"
#include "types/strostream.h"
#include "types/strref.h"
#include "ui/surface.h"

#include <cstdint>

class KeyProcessor;

namespace UI
{

class Menu
{
public:
    class DataSource
    {
    public:
        virtual void getItem(StrOStream& text,
                             KeyId&      keyId,
                             std::size_t index) const = 0;
        
        virtual std::size_t getItemCount() const = 0;
    };

public:
    constexpr Menu(const DataSource& dataSource,
                   Surface&          surface,
                   KeyProcessor&     keyProcessor);

public:
    void createMenu();

private:
    void paintMenu(int     offset,
                   int     start,
                   int     end,
                   uint8_t fg,
                   uint8_t bg);
    
private:
    const DataSource& mDataSource;
    Surface&          mSurface;
    KeyProcessor&     mKeyProcessor;
    int               mSelected;
    
private:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};


inline
constexpr Menu::Menu(const DataSource& dataSource,
                     Surface&          surface,
                     KeyProcessor&     keyProcessor)
    : mDataSource(dataSource)
    , mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mSelected(0)
{ }

}

#endif
