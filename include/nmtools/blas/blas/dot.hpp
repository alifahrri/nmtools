#ifndef NMTOOLS_BLAS_BLAS_DOT_HPP
#define NMTOOLS_BLAS_BLAS_DOT_HPP

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
     * @brief tag to resolve dot operation
     * 
     */
    struct dot_t;
} // namespace nmtools::blas

namespace nmtools::meta
{
    template <typename lhs_t, typename rhs_t>
    struct resolve_optype<void,blas::dot_t,lhs_t,rhs_t>
    {
        static constexpr auto _get()
        {
            if constexpr (std::is_arithmetic_v<lhs_t> && std::is_arithmetic_v<rhs_t>)
                return std::common_type_t<lhs_t,rhs_t>{};
            else if constexpr (meta::is_array1d_v<lhs_t> && meta::is_array1d_v<rhs_t>) {
                using l_t = get_container_value_type_t<lhs_t>;
                using r_t = get_container_value_type_t<rhs_t>;
                using type = std::common_type_t<l_t,r_t>;
                // may be void
                if constexpr (std::is_same_v<type,void>)
                    return detail::fail_t{};
                else return type{};
            }
            else return detail::fail_t{};
        } // _get()
        using type = meta::remove_cvref_t<detail::fail_to_void_t<decltype(_get())>>;
    };
} // namespace nmtools::meta

namespace nmtools::blas
{
    /**
     * @ingroup blas
     * @{
     */
    
    namespace detail
    {
        constexpr auto dot_impl(auto& ret, const auto& v1, const auto& v2, auto n)
        {
            for (size_t i = 0; i < n; i++)
                ret += at(v1,i) * at(v2,i);
        } // dot_impl
    } // namespace detail

    /**
     * @brief dot product of v1 & v2
     * 
     * @tparam V1 vector-like
     * @tparam V2 vector-like
     * @param v1 left-hand-side vector
     * @param v2 right-hand-side vector
     * @return constexpr auto scalar, common type of element v1 & v2
     * @cite gene2013matrix_dot_saxpy
     */
    template <typename V1, typename V2>
    constexpr auto dot(const V1& v1, const V2& v2)
    {
        static_assert(
            (
                meta::is_array1d_v<V1>
                && meta::is_array1d_v<V2>
            ) ||
            /* TODO: consider to drop arithmetic mul for this fn */
            (
                std::is_arithmetic_v<V1>
                && std::is_arithmetic_v<V2>
            )
            , "unsupported type for dot"
        );

        using value_t = meta::resolve_optype_t<dot_t,V1,V2>;
        static_assert( !std::is_same_v<value_t,void>
            , "can't resolve return type for dot"
        );

        using detail::dot_impl;

        /* TODO: consider to drop arithmetic mul for this fn */
        if constexpr (std::is_arithmetic_v<V1>)
            return value_t{v1 * v2};
        else {
            value_t ret{0};
            auto n1 = vector_size(v1);
            auto n2 = vector_size(v2);
            /* TODO: make assertio optional (?) */
            assert(n1==n2);

            dot_impl(ret,v1,v2,n1);

            return ret;
        }
    } // constexpr auto dot(const V1& v1, const V2& v2)

    /** @} */
}

#endif // NMTOOLS_BLAS_BLAS_DOT_HPP