#ifndef INCLUDED_SERIALIZER_H
#define INCLUDED_SERIALIZER_H

#include "storage/storage.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "types/range.h"
#include "macroset.h"
#include "macro.h"

#include <array>

class Event;
class Layer;
class LayerStack;

template <typename T>
struct Serializer
{
    void serialize(const T&, Storage::OStream&);
    bool deserialize(Storage::IStream&, T&);
};

template <>
struct Serializer<MacroSet>
{
    void serialize(const MacroSet& macroSet, Storage::OStream& os);
    bool deserialize(Storage::IStream& is, MacroSet& macroSet);
};

template <>
struct Serializer<Macro>
{
    void serialize(const Macro& macro, Storage::OStream& os);
    bool deserialize(Storage::IStream& is, Macro& macro);
};

template <>
struct Serializer<Layer>
{
    void serialize(const Layer& layer, Storage::OStream& os);
    bool deserialize(Storage::IStream& is, Layer& layer);
};

#endif
