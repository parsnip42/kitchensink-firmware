#ifndef INCLUDED_LAYERPROCESSOR_H
#define INCLUDED_LAYERPROCESSOR_H

class KeyEvent;
class EventQueue;
class KsKeyboard;
class LayerStack;

class LayerProcessor
{
public:
    constexpr explicit LayerProcessor(KsKeyboard& keyboard);

public:
    bool processEvent(LayerStack&     layerStack,
                      const KeyEvent& event,
                      EventQueue&     eventQueue);

private:
    void setLayer(LayerStack& layerStack,
                  int         index,
                  bool        enabled,
                  EventQueue& eventQueue);

    void pressLayer(LayerStack& layerStack,
                    int         index,
                    EventQueue& eventQueue);

    void releaseLayer(LayerStack& layerStack,
                      int         index,
                      EventQueue& eventQueue);

private:
    KsKeyboard& mKeyboard;

private:
    LayerProcessor(const LayerProcessor&) = delete;
    LayerProcessor& operator=(const LayerProcessor&) = delete;

};


inline
constexpr LayerProcessor::LayerProcessor(KsKeyboard& keyboard)
    : mKeyboard(keyboard)
{ }

#endif
