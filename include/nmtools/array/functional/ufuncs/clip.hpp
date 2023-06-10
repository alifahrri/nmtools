#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/clip.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct clip_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::clip(args...);
            }
        };
    }

    constexpr inline auto clip = functor_t(ternary_fmap_t<fun::clip_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::clip_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::clip_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return clip;
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP