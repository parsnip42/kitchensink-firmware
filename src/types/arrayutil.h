#ifndef INCLUDED_ARRAYUTIL_H
#define INCLUDED_ARRAYUTIL_H

#include <array>
#include <cstdint>
#include <tuple>

template<typename Array>
class ArrayUtil
{
private:
    // This class uses variadic templates recursively to create a parameter pack
    // of indices from 0 to Size - 1, and then creates an array from the
    // expanded parameter pack.
    template<std::size_t... Indices>
    class CreateArray;

    // Terminates the sequence by specialising for 0 as the first element
    // (because the parameter pack is created in reverse), then returns an
    // std::array with each element populated from func, ie;
    //     Array{{ func(0), func(1), func(2) }}
    template<std::size_t... Indices>
    class CreateArray<0, Indices...>
    {
    public:
        template <typename Func>
        static constexpr Array create(const Func& func)
        {
            return Array{{ func(0), func(Indices)... }};
        }
    };

    // Recursively creates a new sequence class by adding indices in descending
    // order, ie;
    //     CreateArray<2, 3>::createArray(func)
    //
    // calls;
    //     CreateArray<1, 2, 3>::createArray(func)
    //
    // Until we reach the specialisation above.
    template<std::size_t First, std::size_t... Indices>
    class CreateArray<First, Indices...>
    {
    public:
        template <typename Func>
        static constexpr Array create(const Func& func)
        {
            return CreateArray<First - 1, First, Indices...>::create(func);
        }
    };

public:
    template <typename Func>
    static constexpr Array createArray(const Func& func)
    {
        return CreateArray<std::tuple_size<Array>::value - 1>::create(func);
    }

    template <std::size_t SplitSize>
    static void split(const Array&                                                                       source,
                      std::array<typename Array::value_type, SplitSize>&                                 first,
                      std::array<typename Array::value_type, std::tuple_size<Array>::value - SplitSize>& second)
    {
        std::copy(source.begin(), source.begin() + first.size(), first.begin());
        std::copy(source.begin() + first.size(), source.end(), second.begin());
    }

    template <std::size_t SplitSize>
    static void join(const std::array<typename Array::value_type, SplitSize>&                                 first,
                     const std::array<typename Array::value_type, std::tuple_size<Array>::value - SplitSize>& second,
                     Array&                                                                                   destination)
    {
        std::copy(first.begin(), first.end(), destination.begin());
        std::copy(second.begin(), second.end(), destination.begin() + first.size());
    }
};

#endif


