#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct log_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::log(args...);
            }
        };
    }

    constexpr inline auto log = functor_t(unary_fmap_t<fun::log_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::log_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::log_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return log;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP