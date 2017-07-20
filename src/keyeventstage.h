#ifndef INCLUDED_KEYEVENTSTAGE_H
#define INCLUDED_KEYEVENTSTAGE_H

class KeyEvent;

class KeyEventStage
{
public:
    KeyEventStage() = default;
    virtual ~KeyEventStage() = default;
    
public:
    virtual void processKeyEvent(const KeyEvent& event) = 0;
};

#endif /* INCLUDED_KEYEVENTSTAGE_H */
