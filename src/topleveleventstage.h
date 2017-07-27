#ifndef INCLUDED_TOPLEVELEVENTSTAGE_H
#define INCLUDED_TOPLEVELEVENTSTAGE_H

#include "keyeventstage.h"

#include <algorithm>

class ToplevelEventStage : public KeyEventStage
{
public:
    class OutputGuard
    {
    public:
        OutputGuard(ToplevelEventStage& mTopLevel,
                    KeyEventStage&      next);
        
        ~OutputGuard();
        
    private:
        ToplevelEventStage& mTopLevel;
        KeyEventStage*      mNext;


    private:
        OutputGuard(const OutputGuard&) = delete;
        OutputGuard& operator=(const OutputGuard&) = delete;
        
    private:
        friend class ToplevelEventStage;
    };

public:
    explicit ToplevelEventStage(KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
private:
    KeyEventStage* mNext;
};


inline
ToplevelEventStage::OutputGuard::OutputGuard(ToplevelEventStage& topLevel,
                                             KeyEventStage&      next)
    : mTopLevel(topLevel)
    , mNext(&next)
{
    std::swap(mNext, mTopLevel.mNext);
}

inline
ToplevelEventStage::OutputGuard::~OutputGuard()
{
    std::swap(mNext, mTopLevel.mNext);
}


inline
ToplevelEventStage::ToplevelEventStage(KeyEventStage& next)
    : mNext(&next)
{ }

inline
void ToplevelEventStage::processKeyEvent(const KeyEvent& event)
{
    mNext->processKeyEvent(event);
}

#endif
