#ifndef INCLUDED_KEYMAPSTACK_H
#define INCLUDED_KEYMAPSTACK_H

class KeyMapStack
{
public:
    KeyMapStack();
    
public:
    int getKey(int row, int column);
    
public:
    void setLayer(int layer, const KeyMap& keyMap);
    void pushLayer(int layer);
    void popLayer(int layer);
    
private:
    typedef std::array<KeyMap, 10> Layers;
    typedef std::array<int, 10>    LayerStack;
    
    Layers mLayers;
};

#endif
