#ifndef INCLUDED_TOPLEVELEVENTSTAGE_H
#define INCLUDED_TOPLEVELEVENTSTAGE_H

#include "eventstage.h"

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
        EventStage*      mNext;

    private:
        OutputGuard(const OutputGuard&) = delete;
        OutputGuard& operator=(const OutputGuard&) = delete;
        
    private:
        friend class ToplevelEventStage;
    };

public:
    explicit ToplevelEventStage(EventStage& next);

public:
    virtual void processEvent(const Event& event) override;
    
private:
    EventStage* mNext;
};


inline
ToplevelEventStage::OutputGuard::OutputGuard(ToplevelEventStage& topLevel,
                                             EventStage&      next)
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
ToplevelEventStage::ToplevelEventStage(EventStage& next)
    : mNext(&next)
{ }

inline
void ToplevelEventStage::processEvent(const Event& event)
{
    mNext->processEvent(event);
}

#endif
