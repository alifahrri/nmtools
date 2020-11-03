#ifndef NMTOOLS_BLAS_BLAS_VVADD_HPP
#define NMTOOLS_BLAS_BLAS_VVADD_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"
/* common array (as in matrix/vector) utility */
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools::blas
{
    /**
     * @ingroup blas
     * @{
     */

    namespace detail
    {
        constexpr auto vvadd_impl(auto& ret, const auto& a, const auto& b, auto n)
        {
            for (size_t i=0; i<n; i++)
                at(ret,i) = at(a,i) + at(b,i);
        } // vvadd_impl
    } // namespace 

    /**
     * @brief vector vector addition a+b
     * 
     * @tparam V1 vector-like
     * @tparam V2 vector-like
     * @param v1 lhs
     * @param v2 rhs
     * @return constexpr auto 
     */
    template <typename V1, typename V2>
    constexpr auto vvadd(const V1& a, const V2& b)
    {
        static_assert(
            meta::is_array1d_v<V1>
            && meta::is_array1d_v<V2>,
            "unsupported type for vvadd"
        );

        using meta::remove_cvref_t;
        using meta::get_value_type_or_same_t;
        using meta::transform_bounded_array_t;

        using v1_t = transform_bounded_array_t<V1>;
        using v2_t = transform_bounded_array_t<V2>;

        /* deduce resulting size of matrix */
        constexpr auto is_fixed_size_vec_A = meta::is_fixed_size_vector_v<v1_t>;
        constexpr auto is_fixed_size_vec_B = meta::is_fixed_size_vector_v<v2_t>;

        using e1_t = remove_cvref_t<get_value_type_or_same_t<v1_t>>;
        using e2_t = remove_cvref_t<get_value_type_or_same_t<v2_t>>;
        using return_t = std::common_type_t<e1_t,e2_t>;

        using detail::vvadd_impl;

        /* dispatch compile time ver. */
        if constexpr (is_fixed_size_vec_A && is_fixed_size_vec_B) {
            constexpr auto n1 = fixed_vector_size_v<v1_t>;
            constexpr auto n2 = fixed_vector_size_v<v2_t>;
            constexpr auto n  = n1;

            static_assert (n1==n2);

            auto ret = zeros<v1_t,n>();
            // for (size_t i=0; i<n; i++)
            //     at(ret,i) = at(a,i) + at(b,i);
            vvadd_impl(ret,a,b,n);
            return ret;
        }
        /* dispatch runtime ver. */
        else {
            /* make sure one of the matrix type is resizeable */
            static_assert(
                meta::is_resizeable_v<v1_t> ||
                meta::is_resizeable_v<v2_t>
            );

            auto n1 = size(a);
            auto n2 = size(b);
            /* TODO: make assertio optional (?) */
            assert(n1==n2);
            auto n = n1;

            /* select resizeable mat over fixed ones for return type */
            using return_t = meta::select_resizeable_mat_t<v1_t,v2_t>;
            auto ret = zeros<return_t>(n);
            // for (size_t i=0; i<n; i++)
            //     at(ret,i) = at(a,i) + at(b,i);
            vvadd_impl(ret,a,b,n);
            return ret;
        }
    } // constexpr auto vvadd(const V1& a, const V2& b)

    /** @} */ // end group blas
}

#endif // NMTOOLS_BLAS_BLAS_VVADD_HPP