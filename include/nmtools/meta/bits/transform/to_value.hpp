#ifndef NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/is_constant_adjacency_list.hpp"
#include "nmtools/meta/bits/traits/is_clipped_integer.hpp"
#include "nmtools/meta/bits/transform/promote_index.hpp"
#include "nmtools/meta/bits/transform/clipped_max.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TO_VALUE_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Convert constant index to value
     * 
     * If T is tuple, it is expected to transform to array
     * for easy handling as value.
     * 
     * @tparam T 
     */
    template <typename T,typename=void>
    struct to_value
    {
        static inline constexpr auto value = error::TO_VALUE_UNSUPPORTED<T>{};
    }; // to_value

    template <typename T>
    struct to_value <const T> : to_value<T> {};

    template <typename T>
    struct to_value <T&> : to_value<T> {};

    template <typename T>
    constexpr inline auto to_value_v = to_value<T>::value;

    template <typename T, auto v>
    struct to_value<integral_constant<T,v>>
    {
        static constexpr auto value = v;
    };

    template <>
    struct to_value<none_t>
    {
        static constexpr auto value = none_t{};
    };

    // nmtools' true_type & false_type is not an alias to integral_constant
    template <> struct to_value<true_type>
    { static constexpr auto value = true; };

    template <> struct to_value<false_type>
    { static constexpr auto value = false; };

    // converting nmtools' clipped_integer using meta::to_value means
    // converting the max value to value array
    // note that currently the min value is ignored.
    // this (using max value) is mostly useful for indexing function (where min=0, max=N)
    // to carry the information about maximum number of elements per axis
    // hence we can deduce the maximum number of elements to deduce the type of buffer at compile time

    #if 0
    template <template<typename...>typename Tuple, typename...T, auto...Min, auto...Max>
    struct to_value<
        Tuple<clipped_integer_t<T,Min,Max>...>,
        enable_if_t< is_tuple_v<Tuple<clipped_integer_t<T,Min,Max>...>> && sizeof...(T)>
    >
    {
        using index_t = promote_index_t<T...>;
        static constexpr auto value = nmtools_array{index_t(Max)...};
    }; // to_value

    template <template<typename...>typename tuple, typename...Ts>
    struct to_value<
        tuple<Ts...>
        , enable_if_t< is_tuple_v<tuple<Ts...>> && (is_constant_index_v<Ts> && ...) && sizeof...(Ts)>
    > {
        using index_t = promote_index_t<decltype(Ts::value)...>;
        static constexpr auto value = nmtools_array{index_t(Ts::value)...};
    }; // to_value

    template <template<typename...>typename tuple, typename...Ts>
    struct to_value<
        tuple<Ts...>
        , enable_if_t< is_tuple_v<tuple<Ts...>> && (sizeof...(Ts) == 0)>
    > {
        using index_t = nm_index_t;
        static constexpr auto value = nmtools_array<index_t,0>{};
    }; // to_value

    template <template<typename...>typename tuple, typename...Ts>
    struct to_value<
        tuple<Ts...>
        , enable_if_t< is_constant_adjacency_list_v<tuple<Ts...>> >
    > {
        using tuple_t = tuple<Ts...>;

        constexpr auto value = [](){
            constexpr auto NUM_NODES = sizeof...(Ts);
            constexpr auto MAX_NEIGHBORS = [](){
                auto max = 0;
                meta::template_for<NUM_NODES>([&](auto index){
                    constexpr auto I = decltype(index)::value;
                    auto n_neighbors = len_v<at_t<tuple_t,I>>;
                    max = max > n_neighbors ? max : n_neighbors;
                });
                return max;
            }();
            using inner_t  = nmtools_static_vector<nm_index_t,MAX_NEIGHBORS>;
            using outer_t  = nmtools_array<inner_t,NUM_NODES>;
            using result_t = outer_t;

            auto result = result_t {};

            meta::template_for<NUM_NODES>([&](auto index){
                constexpr auto I = decltype(index)::value;
                using neighbors_t = at_t<tuple_t,I>;
                constexpr auto NEIGHBORS = to_value_v<neighbors_t>;
                for (nm_size_t i=0; i<(nm_size_t)NEIGHBORS.size(); i++) {
                    result[I][i] = at(NEIGHBORS,i);
                }
            });

            return result;
        }();
    };
    #else

    template <template<typename...>typename tuple, typename...Ts>
    struct to_value<
        tuple<Ts...>
        , enable_if_t< is_tuple_v<tuple<Ts...>>>
    > {
        using tuple_t = tuple<Ts...>;

        static constexpr auto value = [](){
            if constexpr (is_constant_adjacency_list_v<tuple<Ts...>>) {
                constexpr auto NUM_NODES = sizeof...(Ts);
                constexpr auto MAX_NEIGHBORS = [](){
                    auto max = 0;
                    meta::template_for<NUM_NODES>([&](auto index){
                        constexpr auto I = decltype(index)::value;
                        auto n_neighbors = len_v<at_t<tuple_t,I>>;
                        max = (nm_index_t)max > (nm_index_t)n_neighbors ? max : n_neighbors;
                    });
                    return max;
                }();
                using inner_t  = nmtools_static_vector<nm_index_t,MAX_NEIGHBORS>;
                using outer_t  = nmtools_array<inner_t,NUM_NODES>;
                using result_t = outer_t;

                auto result = result_t {};

                meta::template_for<NUM_NODES>([&](auto index){
                    constexpr auto I = decltype(index)::value;
                    using neighbors_t = at_t<tuple_t,I>;
                    constexpr auto NUM_NEIGHBORS = len_v<neighbors_t>;
                    result[I].resize(NUM_NEIGHBORS);
                    meta::template_for<NUM_NEIGHBORS>([&](auto index){
                        constexpr auto J = decltype(index)::value;
                        constexpr auto NEIGHBOR = to_value_v<at_t<neighbors_t,J>>;
                        result[I][J] = NEIGHBOR;
                    });
                });

                return result;
            } else if constexpr ((sizeof...(Ts)) && (is_constant_index_v<Ts> && ...)) {
                using index_t = promote_index_t<decltype(Ts::value)...>;
                return nmtools_array{index_t(Ts::value)...};
            } else if constexpr ((sizeof...(Ts)) && (is_clipped_integer_v<Ts> && ...)) {
                using index_t = promote_index_t<decltype(Ts::max)...>;
                return nmtools_array{index_t(Ts::max)...};
            } else {
                using index_t = nm_index_t;
                return nmtools_array<index_t,0>{};   
            }
        }();
    }; // to_value

    #endif

    template <template<typename,auto>typename Array, typename T, auto Min, auto Max, auto N>
    struct to_value<
        Array<clipped_integer_t<T,Min,Max>,N>
    >
    {
        static constexpr auto value = [](){
            using type = nmtools_array<T,N>;
            auto result = type{};
            for (size_t i=0; i<N; i++) {
                result[i] = Max;
            }
            return result;
        }();
    }; // to_value

    template <typename T, auto Min, auto Max>
    struct to_value<clipped_integer_t<T,Min,Max>>
        : clipped_max<clipped_integer_t<T,Min,Max>>
    {};
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_TO_VALUE_HPP