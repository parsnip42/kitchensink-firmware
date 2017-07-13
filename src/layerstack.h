#ifndef INCLUDED_LAYERSTACK_H
#define INCLUDED_LAYERSTACK_H

#include "types/bitmask.h"
#include "keyid.h"
#include "layer.h"

#include <array>
#include <cstdint>

class LayerStack
{
private:
    static constexpr std::size_t MaxLayers = 10;
    
    typedef std::array<Layer, MaxLayers> Layers;
    typedef Bitmask<MaxLayers>           LayerMask;

public:
    typedef Layers::const_iterator const_iterator;
    
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
    constexpr std::size_t size() const;

public:
    const_iterator begin() const;
    const_iterator end() const;
    
private:
    Layers    mLayers;
    LayerMask mLayerMask;

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

inline
constexpr std::size_t LayerStack::size() const
{
    return mLayers.size();
}

inline
LayerStack::const_iterator LayerStack::begin() const
{
    return mLayers.begin();
}

inline
LayerStack::const_iterator LayerStack::end() const
{
    return mLayers.end();
}

#endif
