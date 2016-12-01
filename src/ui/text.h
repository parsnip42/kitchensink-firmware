#ifndef INCLUDED_UI_TEXT_H
#define INCLUDED_UI_TEXT_H

#include "ui/surface.h"

namespace UI
{

class Surface;

class Text
{
public:
    explicit Text(Surface& surface);

public:
    void appendLine(const char* text);

private:
    Surface& mSurface;
    int      mLines;
    
private:
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;
};

}

#endif
