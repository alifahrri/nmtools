#ifndef NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/repeat.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct repeat_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::repeat(args...);
            }
        };
    }

    constexpr inline auto repeat = functor_t(unary_fmap_t<fun::repeat_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::repeat_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::repeat_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return repeat[view.repeats][view.axis];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_REPEAT_HPP