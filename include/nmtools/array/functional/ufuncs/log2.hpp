#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log2.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct log2_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::log2(args...);
            }
        };
    }

    constexpr inline auto log2 = functor_t(unary_fmap_t<fun::log2_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::log2_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::log2_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return log2;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP