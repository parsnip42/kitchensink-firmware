#ifndef INCLUDED_TEXT_H
#define INCLUDED_TEXT_H

class StrRef;
class Surface;

class Text
{
public:
    explicit Text(Surface& surface);

public:
    void appendLine(const StrRef& text);

private:
    Surface& mSurface;
    int      mLines;
    
private:
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;
};

#endif
