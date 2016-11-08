#ifndef INCLUDED_MULTI_H
#define INCLUDED_MULTI_H

#include "keyid.h"

#include <array>
#include <cstdint>

class EventQueue;

class Multi
{
public:
    explicit constexpr Multi(const KeyId& key0 = KeyId::None,
                             const KeyId& key1 = KeyId::None,
                             const KeyId& key2 = KeyId::None,
                             const KeyId& key3 = KeyId::None);
    
public:
    void processEvent(bool pressed, EventQueue& eventQueue);
    
private:
    std::array<KeyId, 4> mKeys;
};


inline
constexpr Multi::Multi(const KeyId& key0,
                       const KeyId& key1,
                       const KeyId& key2,
                       const KeyId& key3)
    : mKeys{{ key3, key2, key1, key0 }}
{ }

#endif
