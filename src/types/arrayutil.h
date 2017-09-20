#ifndef INCLUDED_ARRAYUTIL_H
#define INCLUDED_ARRAYUTIL_H

#include <cstdint>
#include <tuple>

template<typename Array>
class ArrayUtil
{
private:
    // Returns an std::array with each element populated from func. This is
    // achieved by expanding the Indices parameter pack, so it'll usually be
    // called as such;
    //    mapArray<Func, 0, 1, 2>(func)
    //
    // which will then create an array equivalent to;
    //    std::array<T, Size>{{ func(0), func(1), func(2) }}
    template<typename Func, std::size_t... Indices>
    static constexpr Array mapArray(const Func& func)
    { 
        return Array{{ func(Indices)... }};
    }

    // This class uses variadic templates recursively to create a parameter pack
    // of indices from 0 to Size - 1.
    template<std::size_t... Indices>
    class Sequence;

    // Terminates the sequence by specialising for 0 as the first element
    // (because the parameter pack is created in reverse).
    template<std::size_t... Indices>
    class Sequence<0, Indices...>
    {
    public:
        template <typename Func>
        static constexpr Array createArray(const Func& func)
        {
            return mapArray<Func, 0, Indices...>(func);
        }
    };

    // Recursively creates a new sequence class by adding indices in descending
    // order, ie;
    //     Sequence<2, 3>::createArray(func)
    //
    // calls;
    //     Sequence<1, 2, 3>::createArray(func)
    //
    // Until we reach the specialisation above.
    template<std::size_t First, std::size_t... Indices>
    class Sequence<First, Indices...>
    {
    public:
        template <typename Func>
        static constexpr Array createArray(const Func& func)
        {
            return Sequence<First - 1, First, Indices...>::createArray(func);
        }
    };

public:
    template <typename Func>
    static constexpr Array createArray(const Func& func)
    {
        return Sequence<std::tuple_size<Array>::value - 1>::createArray(func);
    }
};

#endif










