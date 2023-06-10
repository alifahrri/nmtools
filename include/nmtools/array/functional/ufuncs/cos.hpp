#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cos.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct cos_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::cos(args...);
            }
        };
    }

    constexpr inline auto cos = functor_t(unary_fmap_t<fun::cos_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::cos_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::cos_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return cos;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP