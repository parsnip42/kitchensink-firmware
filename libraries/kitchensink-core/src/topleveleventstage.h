#ifndef INCLUDED_TOPLEVELEVENTSTAGE_H
#define INCLUDED_TOPLEVELEVENTSTAGE_H

#include "event/eventstage.h"

#include <algorithm>

class ToplevelEventStage : public EventStage
{
public:
    class OutputGuard
    {
    public:
        OutputGuard(ToplevelEventStage& mTopLevel,
                    EventStage&      next);
        
        ~OutputGuard();
        
    private:
        ToplevelEventStage& mTopLevel;
        EventStage*         mNext;

    private:
        OutputGuard(const OutputGuard&) = delete;
        OutputGuard& operator=(const OutputGuard&) = delete;
        
    private:
        friend class ToplevelEventStage;
    };

public:
    ToplevelEventStage();

public:
    virtual bool processEvent(const Event& event) override;
    
private:
    EventStage* mNext;
};


inline
ToplevelEventStage::OutputGuard::OutputGuard(ToplevelEventStage& topLevel,
                                             EventStage&         next)
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
ToplevelEventStage::ToplevelEventStage()
    : mNext(nullptr)
{ }

inline
bool ToplevelEventStage::processEvent(const Event& event)
{
    if (mNext)
    {
        return mNext->processEvent(event);
    }

    return true;
}

#endif
