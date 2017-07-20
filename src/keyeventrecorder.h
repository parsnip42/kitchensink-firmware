#ifndef INCLUDED_MACRORECORDER_H
#define INCLUDED_MACRORECORDER_H

#include "keyevent.h"
#include "keyeventstage.h"

#include <array>
#include <cstdint>

class KeyEventRecorder : public KeyEventStage
{
private:
    typedef std::array<KeyEvent, 200> Content;
    
public:
    typedef Content::const_iterator const_iterator;
    
public:
    KeyEventRecorder(bool           realtime,
                     KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

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
    KeyEventStage& mNext;
};


inline
KeyEventRecorder::const_iterator KeyEventRecorder::begin() const
{
    return mContent.begin();
}

inline
KeyEventRecorder::const_iterator KeyEventRecorder::end() const
{
    return mContent.begin() + mSize;
}

inline
std::size_t KeyEventRecorder::size() const
{
    return mSize;
}

inline
bool KeyEventRecorder::complete() const
{
    return mComplete;
}

inline
bool KeyEventRecorder::full() const
{
    return mSize == mContent.size();
}

#endif /* INCLUDED_MACRORECORDER_H */
