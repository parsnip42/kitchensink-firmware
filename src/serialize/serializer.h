#ifndef INCLUDED_SERIALIZER_H
#define INCLUDED_SERIALIZER_H

#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "types/range.h"
#include "macroset.h"
#include "macro.h"
#include "multikeyset.h"
#include "smartkeyset.h"

#include <array>

class Event;
class Layer;
class LayerStack;
class InStream;
class OutStream;

template <typename T>
struct Serializer
{
    void serialize(const T&, OutStream&);
    bool deserialize(InStream&, T&);
};

template <>
struct Serializer<MacroSet>
{
    void serialize(const MacroSet& macroSet, OutStream& os);
    bool deserialize(InStream& is, MacroSet& macroSet);
};

template <>
struct Serializer<Macro>
{
    void serialize(const Macro& macro, OutStream& os);
    bool deserialize(InStream& is, Macro& macro);
};

template <>
struct Serializer<LayerStack>
{
    void serialize(const LayerStack& layerStack, OutStream& os);
    bool deserialize(InStream& is, LayerStack& layerStack);
};

template <>
struct Serializer<Layer>
{
    void serialize(const Layer& layer, OutStream& os);
    bool deserialize(InStream& is, Layer& layer);
};

template <>
struct Serializer<MultiKeySet>
{
    void serialize(const MultiKeySet& multiKeySet, OutStream& os);
    bool deserialize(InStream& is, MultiKeySet& multiKeySet);
};

template <>
struct Serializer<SmartKeySet>
{
    void serialize(const SmartKeySet& smartKeySet, OutStream& os);
    bool deserialize(InStream& is, SmartKeySet& smartKeySet);
};

#endif
