#ifndef INCLUDED_BENCHMARKSCREEN_H
#define INCLUDED_BENCHMARKSCREEN_H

#include "ui/textscreen.h"
#include "keyeventstage.h"

class Surface;
class EventManager;

class BenchmarkScreen : public KeyEventStage
{
public:
    BenchmarkScreen(Surface&      surface,
                    EventManager& eventManager);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
    void poll();
    
private:
    EventManager& mEventManager;
    Surface&      mSurface;
    TextScreen    mTextScreen;
    bool          mQuit;
};

#endif
