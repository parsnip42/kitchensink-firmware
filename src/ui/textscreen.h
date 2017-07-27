#ifndef INCLUDED_TEXTSCREEN_H
#define INCLUDED_TEXTSCREEN_H

class StrRef;
class Surface;

class TextScreen
{
public:
    explicit TextScreen(Surface& surface);

public:
    void init();
    void appendLine(const StrRef& text);

private:
    Surface& mSurface;
    int      mLines;
    
private:
    TextScreen(const TextScreen&) = delete;
    TextScreen& operator=(const TextScreen&) = delete;
};

#endif
