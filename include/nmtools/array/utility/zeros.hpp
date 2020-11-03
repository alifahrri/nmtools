#ifndef NMTOOLS_ARRAY_UTILITY_ZEROS_HPP
#define NMTOOLS_ARRAY_UTILITY_ZEROS_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
    /* make symbols accessible for unqualified-lookup */
    using std::get;
    using std::size;
    using std::fabs;
    using std::sqrt;
    using std::tuple_size;
    using std::tuple_size_v;

    /**
     * @brief make zeros array, given size known at compile-time
     * 
     * @tparam Array vector-like
     * @tparam n number of elements
     * @return constexpr auto 
     */
    template <typename Array, size_t N>
    constexpr auto zeros()
    {
        static_assert(
            meta::is_array1d_v<Array> && meta::has_value_type_v<Array>,
            "unsupported type Array for zeros<size_t>"
        );
        /* deduce type using helper metafunction 
            to allows partial specialization for
                arbitraty custom type Array*/
        using return_t = meta::make_zeros_vector_t<Array,N>;
        /* make sure valid type */
        static_assert(!std::is_same_v<return_t,void>);
        /* assuming the deduced type can be instantiated this way */
        auto zero = return_t{};
        return zero;
    } // constexpr auto zeros()

    /**
     * @brief make zeros array, given size & type
     * 
     * @tparam Array matrix-like, resizeable
     * @param m number of rows
     * @param n number of columns
     * @return constexpr auto
     */
    template <typename Array, typename size_type>
    auto zeros(size_type m, size_type n)
    {
        static_assert(
            /* TODO: consider to use is_matrix_like instead of is_array2d */
            meta::is_array2d_v<Array> &&
            (
                meta::is_resizeable_v<Array>
                || meta::is_resizeable2d_v<Array>
            ),
            "unsupported type Array for zeros(size_t,size_t)"
        );
        /* TODO: make sure Array can be constructed this way */
        auto z = Array{};
        /* TODO: consider to provide free function resize */
        /* can directly resize with m, n as arguments */
        if constexpr (meta::is_resizeable2d_v<Array>)
            z.resize(m,n);
        /* doesnt have resize 2d, let's resize each elements */
        else {
            z.resize(m);
            if constexpr (meta::is_resizeable_v<meta::remove_cvref_t<decltype(at(z,0))>>)
                for (size_t i=0; i<size(z); i++)
                    at(z,i).resize(n);
            else {
                /* assuming at(z,0) has fixed size n */
                /* TODO: make assertion optional (?) */
                constexpr auto N = fixed_vector_size_v<meta::remove_cvref_t<decltype(at(z,0))>>;
                assert (N==n);
            }
        }
        return z;
    } // auto zeros(size_t m, size_t n)

    /**
     * @brief make zeros array, given size known at compile-time
     * 
     * @tparam m number of rows
     * @tparam n number of columns
     * @tparam Array matrix-like, has_tuple_size, has_value_type
     * @return constexpr auto 
     */
    template <typename Array, size_t M, size_t N>
    constexpr auto zeros()
    {
        static_assert(
            meta::is_array2d_v<Array>
            && meta::is_fixed_size_matrix_v<Array>,
            "unsupported type Array for zeros<size_t,size_t>()"
        );        
        using return_t = meta::make_zeros_matrix_t<Array,M,N>;
        static_assert(!std::is_same_v<return_t,void>);
        auto z = return_t{};
        return z;
    } // constexpr auto zeros()

    /**
     * @brief make zeros array, given size & type
     * 
     * @tparam Array vector-like
     * @param n number of elements
     * @return constexpr auto 
     */
    template <typename Array>
    auto zeros(size_t n)
    {
        static_assert(
            meta::is_array1d_v<Array>
            && meta::is_resizeable_v<Array>,
            "unsupported type Array for zeros(size_t)"
        );
        auto z = Array{};
        z.resize(n);
        return z;
    } // auto zeros(size_t n)
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_ZEROS_HPP