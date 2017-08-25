#ifndef INCLUDED_EVENTRECORDER_H
#define INCLUDED_EVENTRECORDER_H

#include "event/event.h"
#include "event/eventstage.h"

#include <array>
#include <cstdint>

class EventRecorder : public EventStage
{
private:
    typedef std::array<Event, 200> Content;
    
public:
    typedef Content::const_iterator const_iterator;
    
public:
    explicit EventRecorder(bool realtime);

public:
    virtual bool processEvent(const Event& event) override;

public:
    const_iterator begin() const;
    const_iterator end() const;
    std::size_t size() const;
    bool complete() const;
    bool full() const;
    
private:
    uint32_t       mLastMs;
    bool           mRealtime;
    Content        mContent;
    std::size_t    mSize;
    bool           mComplete;
};


inline
EventRecorder::const_iterator EventRecorder::begin() const
{
    return mContent.begin();
}

inline
EventRecorder::const_iterator EventRecorder::end() const
{
    return mContent.begin() + mSize;
}

inline
std::size_t EventRecorder::size() const
{
    return mSize;
}

inline
bool EventRecorder::complete() const
{
    return mComplete;
}

inline
bool EventRecorder::full() const
{
    return mSize == mContent.size();
}

#endif
