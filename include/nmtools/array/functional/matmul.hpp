#ifndef NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/matmul.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct matmul_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::matmul(args...);
            }
        };
    }

    constexpr inline auto matmul = functor_t(binary_fmap_t<fun::matmul_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::matmul_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::matmul_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return matmul;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_MATMUL_HPP