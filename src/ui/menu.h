#ifndef INCLUDED_UI_MENU_H
#define INCLUDED_UI_MENU_H

namespace UI
{

class Surface;

class Menu
{
public:
    explicit Menu(Surface& surface);

public:
    void paint();
    
private:
    Surface& mSurface;

private:
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};

}

#endif
