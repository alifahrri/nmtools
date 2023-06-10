#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/signbit.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct signbit_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::signbit(args...);
            }
        };
    }

    constexpr inline auto signbit = functor_t(unary_fmap_t<fun::signbit_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::signbit_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::signbit_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return signbit;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP