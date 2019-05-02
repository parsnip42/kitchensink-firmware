#ifndef INCLUDED_LAYERSTACK_H
#define INCLUDED_LAYERSTACK_H

#include "types/bitmask.h"
#include "event/event.h"
#include "layer.h"
#include "config.h"

#include <array>
#include <cstdint>

class LayerStack
{
public:
    typedef Bitmask<Config::kLayerCount> Mask;
    
private:
    typedef std::array<Layer, Config::kLayerCount> Layers;

public:
    typedef Layers::const_iterator const_iterator;
    
public:
    LayerStack() = default;

public:
    Event at(const Mask& layerMask,
             int         row,
             int         column) const;
    
    int activeLayer(const Mask& layerMask,
                    int         row,
                    int         column) const;
    
    Event atIndex(int index,
                  int row,
                  int column) const;

    void clear();
    
public:
    const Layer& operator[](std::size_t n) const;
    Layer& operator[](std::size_t n);
    std::size_t size() const;

public:
    const_iterator begin() const;
    const_iterator end() const;
    
private:
    Layers mLayers;

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
std::size_t LayerStack::size() const
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
