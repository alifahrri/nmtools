#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/concatenate.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct concatenate_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::concatenate(args...);
            }
        };
    }

    constexpr inline auto concatenate = functor_t{binary_fmap_t<fun::concatenate_t>{}};

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::concatenate_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::concatenate_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return concatenate[view.axis];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP