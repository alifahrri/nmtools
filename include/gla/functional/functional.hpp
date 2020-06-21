#ifndef GLA_FUNCTIONAL_FUNCTIONAL_HPP
#define GLA_FUNCTIONAL_FUNCTIONAL_HPP

#include "gla/utils/traits.hpp"
#include <tuple>

namespace gla
{
    template <typename functional_impl>
    struct functional_base : functional_impl
    {
        using impl_t = functional_impl;

        template <typename MatrixType>
        static auto lu_decomposition(const MatrixType& matrix)
        {
            static_assert(
                utils::traits::has_lu_decomposition_v<impl_t, const MatrixType&>,
                "dev notes : lu_decomposition not implemented"                
            );
            /* TODO : check return type */
            auto [l, u] = impl_t::lu_decomposition(matrix);
            return std::make_tuple(l,u);
        }

        template <typename MatrixType>
        static auto inverse(const MatrixType& matrix)
        {
            static_assert(
                utils::traits::has_inverse_v<impl_t, const MatrixType&>,
                "dev notes : inverse not implemented"
            );
            /* TODO : check return type */
            auto inv = impl_t::inverse(matrix);
            return inv;
        }

        template <typename MatrixType>
        static auto transpose(const MatrixType& matrix)
        {
            static_assert(
                utils::traits::has_transpose_v<impl_t, const MatrixType&>,
                "dev notes : transpose not implemented"
            );
            /* TODO : check return type */
            auto transposed = impl_t::transpose(matrix);
            /* */
            return transposed;
        }
    };
    
} // namespace gla

#endif // GLA_FUNCTIONAL_FUNCTIONAL_HPP