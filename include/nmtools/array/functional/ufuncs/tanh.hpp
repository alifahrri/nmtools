#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/tanh.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct tanh_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::tanh(args...);
            }
        };
    }

    constexpr inline auto tanh = functor_t(unary_fmap_t<fun::tanh_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::tanh_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::tanh_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return tanh;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP