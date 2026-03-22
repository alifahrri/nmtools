#ifndef NMTOOLS_META_HPP
#define NMTOOLS_META_HPP


// stl.hpp define basic sctructure (array, tuple, vector, maybe...)
// using std:: if possible, auto fallback to utl::
#include "nmtools/stl.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/platform.hpp"

// must include first, prefer stl
#ifndef NMTOOLS_DISABLE_STL
#include "nmtools/meta/stl.hpp"
#endif // NMTOOLS_DISABLE_STL

// TODO: prioritize boost as default
#include "nmtools/meta/utl.hpp"

// TODO: prioritize boost as default
#ifdef NMTOOLS_ENABLE_BOOST
#include "nmtools/meta/boost.hpp"
#endif

#include "nmtools/meta/traits.hpp"
#include "nmtools/meta/transform.hpp"
#include "nmtools/meta/array.hpp"

namespace nmtools::meta
{
    // TODO: remove, cleanup fixed shape design
    template <typename T, size_t N>
    struct nested_array_size<T[N]>
    {
        static constexpr auto value = N;
    };

    // defined here since we need nmtools_array
    template <typename T, auto N>
    struct fixed_shape<T[N]>
    {
        static constexpr auto value = [](){
            if constexpr (is_num_v<T>) {
                using type = nmtools_array<size_t,1>;
                return type{N};
            } else if constexpr (is_bounded_array_v<T>) {
                auto shape = fixed_shape_v<T>;
                using shape_t = decltype(shape);
                constexpr auto len = len_v<shape_t>;
                using type = nmtools_array<size_t,1+len>;
                auto new_shape = type{};
                for (size_t i=0; i<len; i++) {
                    // assume has operator[]
                    new_shape[len-i] = shape[len-i-1];
                }
                new_shape[0] = N;
                return new_shape;
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<T[N]>{};
            }
        }();
    };

    template <template<typename...>typename Tuple, typename...Ts, auto...Min, auto...Max>
    struct clipped_max<
        Tuple<clipped_integer_t<Ts,Min,Max>...>,
        enable_if_t< is_tuple_v<Tuple<clipped_integer_t<Ts,Min,Max>...>> >
    >
    {
        using index_t = promote_index_t<Ts...>;
        static constexpr auto value = nmtools_array{index_t(Max)...};
    };

    template <template<typename...>typename Tuple, typename...Ts, auto...Min, auto...Max>
    struct clipped_min<
        Tuple<clipped_integer_t<Ts,Min,Max>...>,
        enable_if_t< is_tuple_v<Tuple<clipped_integer_t<Ts,Min,Max>...>> >
    >
    {
        using index_t = promote_index_t<Ts...>;
        static constexpr auto value = nmtools_array{index_t(Min)...};
    };

    // converting nmtools' clipped_integer using meta::max_value means
    // converting the max value to value array
    // note that currently the min value is ignored.
    // this (using max value) is mostly useful for indexing function (where min=0, max=N)
    // to carry the information about maximum number of elements per axis
    // hence we can deduce the maximum number of elements to deduce the type of buffer at compile time

    template <template<typename...>typename Tuple, typename...T, auto...Min, auto...Max>
    struct max_value<
        Tuple<clipped_integer_t<T,Min,Max>...>,
        enable_if_t< is_tuple_v<Tuple<clipped_integer_t<T,Min,Max>...>> && sizeof...(T)>
    >
    {
        using index_t = promote_index_t<T...>;
        static constexpr auto value = nmtools_array{index_t(Max)...};
    }; // max_value

    template <template<typename...>typename tuple, typename...Ts>
    struct max_value<
        tuple<Ts...>
        , enable_if_t< is_tuple_v<tuple<Ts...>> && (is_constant_index_v<Ts> && ...) && sizeof...(Ts)>
    > {
        using index_t = promote_index_t<decltype(Ts::value)...>;
        static constexpr auto value = nmtools_array{index_t(Ts::value)...};
    }; // max_value

    template <template<typename,auto>typename Array, typename T, auto Min, auto Max, auto N>
    struct max_value<
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
    }; // max_value

    template <template<typename...>typename Tuple, typename...T, auto...Min, auto...Max>
    struct min_value<
        Tuple<clipped_integer_t<T,Min,Max>...>,
        enable_if_t< is_tuple_v<Tuple<clipped_integer_t<T,Min,Max>...>> && sizeof...(T)>
    >
    {
        using index_t = promote_index_t<T...>;
        static constexpr auto value = nmtools_array{index_t(Min)...};
    }; // min_value

    template <template<typename...>typename tuple, typename...Ts>
    struct min_value<
        tuple<Ts...>
        , enable_if_t< is_tuple_v<tuple<Ts...>> && (is_constant_index_v<Ts> && ...) && sizeof...(Ts)>
    > {
        using index_t = promote_index_t<decltype(Ts::value)...>;
        static constexpr auto value = nmtools_array{index_t(Ts::value)...};
    }; // min_value

    template <template<typename,auto>typename Array, typename T, auto Min, auto Max, auto N>
    struct min_value<
        Array<clipped_integer_t<T,Min,Max>,N>
    >
    {
        static constexpr auto value = [](){
            using type = nmtools_array<T,N>;
            auto result = type{};
            for (size_t i=0; i<N; i++) {
                result[i] = Min;
            }
            return result;
        }();
    }; // min_value

    /**
     * @brief overloaded version of transform_bounded_array for T[N]
     * 
     * @tparam T element type
     * @tparam N number of elements
     */
    template <typename T, size_t N>
    struct transform_bounded_array<T[N]>
    {
        using value_type = typename transform_bounded_array<remove_cvref_t<T>>::type;
        using type = nmtools_array<remove_cvref_t<value_type>,N>;
    };

    template <typename T, typename>
    struct tuple_to_array
    {
        static constexpr auto vtype = [](){
            if constexpr (is_tuple_v<T>) {
                auto element_vtype = [](){
                    using element_t = get_common_type_t<T>;
                    if constexpr (is_constant_index_v<element_t>) {
                        return as_value_v<typename element_t::value_type>;
                    } else {
                        return as_value_v<element_t>;
                    }
                }();
                using element_t = type_t<decltype(element_vtype)>;
                constexpr auto N = len_v<T>;
                return as_value_v<nmtools_array<element_t,N>>;
            } else {
                return as_value_v<T>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // tuple_to_array

    template <typename T, typename>
    struct fixed_ndarray_shape
    {
        /**
         * @brief get the shape of ndarray.
         *
         * Dispatched code based on the attributes, with the following order:
         * - T is nested array and has fixed-size
         * - T is bounded array
         * - fail
         * 
         * @return constexpr auto 
         */
        static constexpr auto value = [](){
            // check for fixed-size array (that has tuple_size_v)
            if constexpr (nested_array_size_v<T> > 0) {
                // nested_array_dim_v mimics std rank_v
                // nested_array_size_v mimics std extent_v
                constexpr auto dim = nested_array_dim_v<T>;
                using array_t = nmtools_array<size_t,dim>;
                auto shape = array_t{};
                template_for<dim>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    using nested_t = remove_nested_array_dim_t<T,i>;
                    shape[i] = nested_array_size_v<nested_t>;
                });
                return shape;
            }
            // fail otherwise
            else return detail::fail_t{};
        }();
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    };

    template <typename T, auto N, auto M>
    struct resize_size<T[N],M>
    {
        using type = nmtools_array<T,M>;
    };
}

#endif // NMTOOLS_META_HPP