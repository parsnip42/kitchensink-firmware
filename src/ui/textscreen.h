#ifndef INCLUDED_TEXTSCREEN_H
#define INCLUDED_TEXTSCREEN_H

#include "types/circularbuffer.h"
#include "types/strbuf.h"

class StrRef;
class Surface;

class TextScreen
{
private:
    typedef StrBuf<48> Line;
    
public:
    explicit TextScreen(Surface& surface);

public:
    void init();
    void appendLine(const StrRef& text);

private:
    Surface&                 mSurface;
    CircularBuffer<Line, 24> mContent;

private:
    TextScreen(const TextScreen&) = delete;
    TextScreen& operator=(const TextScreen&) = delete;
};

#endif
