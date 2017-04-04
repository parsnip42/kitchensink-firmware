#ifndef INCLUDED_UI_TEXT_H
#define INCLUDED_UI_TEXT_H

namespace Types { class StrRef; }
namespace UI { class Surface; }

namespace UI
{

class Text
{
public:
    explicit Text(Surface& surface);

public:
    void appendLine(const Types::StrRef& text);

private:
    Surface& mSurface;
    int      mLines;
    
private:
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;
};

}

#endif
