#ifndef INCLUDED_KEYCONFIGSCREEN_H
#define INCLUDED_KEYCONFIGSCREEN_H

#include "ui/labelwidget.h"
#include "keyeventstage.h"

class Widget;

class KeyConfigScreen : public KeyEventStage
{
public:
    KeyConfigScreen();

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    Widget& rootWidget();
    
private:
    LabelWidget mLabel;
    
private:
    KeyConfigScreen(const KeyConfigScreen&) = delete;
    KeyConfigScreen& operator=(const KeyConfigScreen&) = delete;
};

#endif
