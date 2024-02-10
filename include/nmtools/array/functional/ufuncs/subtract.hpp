#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct subtract_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::subtract(args...);
            }
        };

        struct reduce_subtract_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reduce_subtract(args...);
            }
        };

        struct outer_subtract_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::outer_subtract(args...);
            }
        };

        struct accumulate_subtract_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::accumulate_subtract(args...);
            }
        };
    }

    constexpr inline auto subtract = functor_t(binary_fmap_t<fun::subtract_t>{});
    
    constexpr inline auto reduce_subtract = functor_t(unary_fmap_t<fun::reduce_subtract_t>{});

    constexpr inline auto outer_subtract = functor_t(binary_fmap_t<fun::outer_subtract_t>{});

    constexpr inline auto accumulate_subtract = functor_t(unary_fmap_t<fun::accumulate_subtract_t>{});

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::subtract_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::subtract_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;
        using array_type = typename view_type::array_type;
        using lhs_array_type = meta::at_t<array_type,0>;
        using rhs_array_type = meta::at_t<array_type,1>;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            if constexpr (
                meta::is_view_v<lhs_array_type>
                && meta::is_view_v<rhs_array_type>
                && !meta::is_same_view_v<view::broadcast_to_t,lhs_array_type>
                && !meta::is_same_view_v<view::broadcast_to_t,rhs_array_type>
            ) {
                return subtract
                    * get_function(nmtools::get<1>(view.array))
                    * get_function(nmtools::get<0>(view.array))
                ;
            } else if constexpr (
                meta::is_view_v<lhs_array_type>
                && !meta::is_same_view_v<view::broadcast_to_t,lhs_array_type>
            ) {
                return subtract
                    * get_function(nmtools::get<0>(view.array))
                ;
            } else if constexpr (
                meta::is_view_v<rhs_array_type>
                && !meta::is_same_view_v<view::broadcast_to_t,rhs_array_type>
            ) {
                // TODO: reverse operands
                return subtract
                    * get_function(nmtools::get<1>(view.array))
                ;
            } else {
                return subtract;
            }
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::reduce_t, view::subtract_t<lhs_t,rhs_t,res_t>, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::reduce_t, view::subtract_t<lhs_t,rhs_t,res_t>, args_t...
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
            return reduce_subtract[view.axis][dtype][view.initial][view.keepdims];
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::outer_t, view::subtract_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::outer_t, view::subtract_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return outer_subtract;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::accumulate_t, view::subtract_t<lhs_t,rhs_t,res_t>, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::accumulate_t, view::subtract_t<lhs_t,rhs_t,res_t>, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return accumulate_subtract[view.axis];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP