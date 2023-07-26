#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct add_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::add(args...);
            }
        };

        struct reduce_add_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reduce_add(args...);
            }
        };

        struct outer_add_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::outer_add(args...);
            }
        };

        struct accumulate_add_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::accumulate_add(args...);
            }
        };
    }

    constexpr inline auto add = functor_t(binary_fmap_t<fun::add_t>{});
    
    constexpr inline auto reduce_add = functor_t(unary_fmap_t<fun::reduce_add_t>{});

    constexpr inline auto outer_add = functor_t(binary_fmap_t<fun::outer_add_t>{});

    constexpr inline auto accumulate_add = functor_t(unary_fmap_t<fun::accumulate_add_t>{});

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::add_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::add_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return add;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::reduce_t, view::add_t<lhs_t,rhs_t,res_t>, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::reduce_t, view::add_t<lhs_t,rhs_t,res_t>, args_t...
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
            return reduce_add[view.axis][dtype][view.initial][view.keepdims];
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::outer_t, view::add_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::outer_t, view::add_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return outer_add;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::accumulate_t, view::add_t<lhs_t,rhs_t,res_t>, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::accumulate_t, view::add_t<lhs_t,rhs_t,res_t>, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return accumulate_add[view.axis];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP