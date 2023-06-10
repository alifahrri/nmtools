#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arctanh.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct arctanh_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::arctanh(args...);
            }
        };
    }

    constexpr inline auto arctanh = functor_t(unary_fmap_t<fun::arctanh_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::arctanh_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::arctanh_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return arctanh;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP