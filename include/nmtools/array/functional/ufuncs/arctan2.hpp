#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arctan2.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct arctan2_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const noexcept
            {
                return view::arctan2(args...);
            }
        };
    }

    constexpr inline auto arctan2 = functor_t{binary_fmap_t<fun::arctan2_t>{}};

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::arctan2_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::arctan2_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
           return arctan2; 
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP