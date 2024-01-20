#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/minimum.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct minimum_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::minimum(args...);
            }
        };

        struct reduce_minimum_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reduce_minimum(args...);
            }
        };

        struct outer_minimum_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::outer_minimum(args...);
            }
        };

        struct accumulate_minimum_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::accumulate_minimum(args...);
            }
        };
    }

    constexpr inline auto minimum = functor_t(binary_fmap_t<fun::minimum_t>{});
    
    constexpr inline auto reduce_minimum = functor_t(unary_fmap_t<fun::reduce_minimum_t>{});

    constexpr inline auto outer_minimum = functor_t(binary_fmap_t<fun::outer_minimum_t>{});

    constexpr inline auto accumulate_minimum = functor_t(unary_fmap_t<fun::accumulate_minimum_t>{});

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::minimum_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::minimum_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return minimum;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::reduce_t, view::minimum_t<lhs_t,rhs_t,res_t>, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::reduce_t, view::minimum_t<lhs_t,rhs_t,res_t>, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto dtype = [](){
                if constexpr (is_none_v<res_t>) {
                    return res_t{};
                } else {
                    return dtype_t<res_t>{};
                }
            }();
            return reduce_minimum[view.axis][dtype][view.initial][view.keepdims];
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::outer_t, view::minimum_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::outer_t, view::minimum_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return outer_minimum;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::accumulate_t, view::minimum_t<lhs_t,rhs_t,res_t>, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::accumulate_t, view::minimum_t<lhs_t,rhs_t,res_t>, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return accumulate_minimum[view.axis];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP