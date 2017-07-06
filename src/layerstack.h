#ifndef INCLUDED_LAYERSTACK_H
#define INCLUDED_LAYERSTACK_H

#include "types/bitmask.h"
#include "keyid.h"
#include "layer.h"

#include <array>
#include <cstdint>

class LayerStack
{
public:
    static constexpr std::size_t MaxLayers = 10;
    
private:
    typedef std::array<Layer, MaxLayers> Layers;

public:
    LayerStack() = default;

public:
    KeyId at(int row, int column) const;
    int activeLayer(int row, int column) const;
    KeyId atIndex(int index, int row, int column) const;
    
public:
    void setLayer(int index, bool enabled);
    bool enabled(int index) const;
    
public:
    const Layer& operator[](std::size_t n) const;
    Layer& operator[](std::size_t n);
    
private:
    Layers             mLayers;
    Bitmask<MaxLayers> mLayerMask;

private:
    LayerStack(const LayerStack&) = delete;
    LayerStack& operator=(const LayerStack&) = delete;
};


inline
const Layer& LayerStack::operator[](std::size_t n) const
{
    return mLayers[n];
}

inline
Layer& LayerStack::operator[](std::size_t n)
{
    return mLayers[n];
}

#endif
