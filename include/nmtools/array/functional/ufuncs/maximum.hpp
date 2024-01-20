#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/maximum.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct maximum_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::maximum(args...);
            }
        };

        struct reduce_maximum_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reduce_maximum(args...);
            }
        };

        struct outer_maximum_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::outer_maximum(args...);
            }
        };

        struct accumulate_maximum_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::accumulate_maximum(args...);
            }
        };
    }

    constexpr inline auto maximum = functor_t(binary_fmap_t<fun::maximum_t>{});
    
    constexpr inline auto reduce_maximum = functor_t(unary_fmap_t<fun::reduce_maximum_t>{});

    constexpr inline auto outer_maximum = functor_t(binary_fmap_t<fun::outer_maximum_t>{});

    constexpr inline auto accumulate_maximum = functor_t(unary_fmap_t<fun::accumulate_maximum_t>{});

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::maximum_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::maximum_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return maximum;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::reduce_t, view::maximum_t<lhs_t,rhs_t,res_t>, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::reduce_t, view::maximum_t<lhs_t,rhs_t,res_t>, args_t...
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
            return reduce_maximum[view.axis][dtype][view.initial][view.keepdims];
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::outer_t, view::maximum_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::outer_t, view::maximum_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return outer_maximum;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::accumulate_t, view::maximum_t<lhs_t,rhs_t,res_t>, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::accumulate_t, view::maximum_t<lhs_t,rhs_t,res_t>, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return accumulate_maximum[view.axis];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP