#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/isinf.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct isinf_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::isinf(args...);
            }
        };
    }

    constexpr inline auto isinf = functor_t(unary_fmap_t<fun::isinf_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::isinf_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::isinf_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return isinf;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP