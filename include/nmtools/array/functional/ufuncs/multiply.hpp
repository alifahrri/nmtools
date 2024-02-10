#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct multiply_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::multiply(args...);
            }
        };

        struct reduce_multiply_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reduce_multiply(args...);
            }
        };

        struct outer_multiply_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::outer_multiply(args...);
            }
        };

        struct accumulate_multiply_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::accumulate_multiply(args...);
            }
        };
    }

    constexpr inline auto multiply = functor_t(binary_fmap_t<fun::multiply_t>{});

    constexpr inline auto reduce_multiply = functor_t(unary_fmap_t<fun::reduce_multiply_t>{});

    constexpr inline auto outer_multiply = functor_t(binary_fmap_t<fun::outer_multiply_t>{});

    constexpr inline auto accumulate_multiply = functor_t(unary_fmap_t<fun::accumulate_multiply_t>{});

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::multiply_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::multiply_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return multiply;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::reduce_t, view::multiply_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::reduce_t, view::multiply_t<lhs_t,rhs_t,res_t>, arrays_t...
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
            return reduce_multiply[view.axis][dtype][view.initial][view.keepdims];
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::outer_t, view::multiply_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::outer_t, view::multiply_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return outer_multiply;
        }
    };

    template <typename lhs_t, typename rhs_t, typename res_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::accumulate_t, view::multiply_t<lhs_t,rhs_t,res_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::accumulate_t, view::multiply_t<lhs_t,rhs_t,res_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return accumulate_multiply[view.axis];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP