#ifndef INCLUDED_STORAGESCREEN_H
#define INCLUDED_STORAGESCREEN_H

#include "ui/textscreen.h"
#include "keyeventstage.h"

class Surface;
class EventManager;

class StorageScreen : public KeyEventStage
{
public:
    StorageScreen(Surface&      surface,
                  EventManager& eventManager);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
    void poll();
    
private:
    EventManager& mEventManager;
    TextScreen    mTextScreen;
    bool          mQuit;
};

#endif
