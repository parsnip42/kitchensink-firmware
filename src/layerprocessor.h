#ifndef INCLUDED_LAYERPROCESSOR_H
#define INCLUDED_LAYERPROCESSOR_H

#include "keyeventstage.h"

class KeySource;
class KeyEvent;

class LayerProcessor : public KeyEventStage
{
public:
    explicit LayerProcessor(KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

public:
    KeySource* keySource;
    
private:
    KeyEventStage& mNext;
    
private:
    LayerProcessor(const LayerProcessor&) = delete;
    LayerProcessor& operator=(const LayerProcessor&) = delete;
};

#endif
