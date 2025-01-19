#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FUNCTION_COMPOSITION_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FUNCTION_COMPOSITION_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    template <typename view_t>
    struct get_function_composition_t;

    template <typename view_type>
    constexpr auto get_function_composition(const view_type& view)
    {
        if constexpr (meta::is_maybe_v<view_type>) {
            using result_type = meta::remove_cvref_t<decltype(get_function_composition(*view))>;
            using return_type = nmtools_maybe<result_type>;
            return (view
                ? return_type{get_function_composition(*view)}
                : return_type{meta::Nothing}
            );
        } else {
            auto get_fn = get_function_composition_t<view_type>{view};
            return get_fn();
        }
    } // get_function_composition

    template <template<typename...>typename view_t, typename...args_t>
    struct get_function_composition_t<
        view::decorator_t<view_t,args_t...>
    > {
        using view_type = view::decorator_t<view_t,args_t...>;
        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto function = get_function(view);
            auto operands = get_operands(view);
            static_assert( !meta::is_fail_v<decltype(operands)> );
            constexpr auto N = view_type::arity;
            auto composition = meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                constexpr auto r_index = meta::ct_v<(N-1)-I>;
                const auto& operand = nmtools::at(operands,r_index);
                using operand_t = meta::remove_pointer_t<meta::remove_cvref_t<decltype(operand)>>;
                static_assert(
                    (meta::is_view_v<operand_t>)
                    || ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                        && !meta::is_view_v<operand_t>
                    )
                );
                // skip alias
                if constexpr (meta::is_same_view_v<view::alias_t,operand_t>) {
                    // finish
                    return init;
                } else if constexpr (meta::is_view_v<operand_t>) {
                    auto sub_composition = get_function_composition(operand);
                    return init * sub_composition;
                } else if constexpr ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                    && !meta::is_view_v<operand_t>
                ) {
                    return init;
                }
            }, function);
            return composition;
        }
    }; // get_function_composition_t

    template <typename...args_t>
    struct get_function_composition_t<
        view::decorator_t<
            view::ufunc_t, args_t...
        >
    > {
        using view_type = view::decorator_t<view::ufunc_t, args_t...>;
        using view_id_type = typename view_type::id_type;
        view_type view;

        constexpr auto operator()() const noexcept 
        {
            auto function = get_function(view);
            auto operands = get_operands(view);
            static_assert( !meta::is_fail_v<decltype(operands)> );
            constexpr auto N = view_type::arity;
            auto composition = meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                constexpr auto r_index = meta::ct_v<(N-1)-I>;
                const auto& operand = at(operands,r_index);
                using operand_t = meta::remove_pointer_t<meta::remove_cvref_t<decltype(operand)>>;
                static_assert(
                    (meta::is_view_v<operand_t>)
                    || ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                        && !meta::is_view_v<operand_t>
                    )
                );
                #if 1
                if constexpr (meta::is_broadcast_view_v<operand_t>) {
                    // TODO: refactor ufuncs
                    // skip broadcasting
                    const auto& sub_operand = at(get_operands(operand),meta::ct_v<0>);
                    static_assert( !meta::is_fail_v<decltype(sub_operand)> );
                    using sub_operand_t = meta::remove_pointer_t<meta::remove_cvref_t<decltype(sub_operand)>>;
                    if constexpr (meta::is_same_view_v<view::alias_t,sub_operand_t>) {
                        // finish
                        return init;
                    } else if constexpr (meta::is_view_v<sub_operand_t>) {
                        return init * get_function_composition(sub_operand);
                    } else if constexpr (
                        (meta::is_num_v<sub_operand_t> || meta::is_ndarray_v<sub_operand_t>)
                        && !meta::is_view_v<sub_operand_t>
                    ) {
                        return init;
                    }
                } else
                #endif
                if constexpr (meta::is_view_v<operand_t>) {
                    return init * get_function_composition(operand);
                } else if constexpr (
                    (meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                    && !meta::is_view_v<operand_t>
                ) {
                    return init;
                }
            }, function);
            return composition;
        }
    }; // get_function_composition_t
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FUNCTION_COMPOSITION_HPP