#ifndef NMTOOLS_CORE_FOLD_HPP
#define NMTOOLS_CORE_FOLD_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/apply.hpp"
#include "nmtools/core/combinator.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::functional
{
    template <typename view_t>
    constexpr auto fold(const view_t& view);

    template <typename state_t, typename operand_t>
    constexpr auto fold_operand(state_t state, const operand_t& operand)
    {
        const auto& m_operand = [&]() -> decltype(auto) {
            if constexpr (is_pointer_v<operand_t>) {
                return (*operand);
            } else {
                return (operand);
            }
        }();
        using m_operand_t = remove_cvref_t<decltype(m_operand)>;
        using utility::tuple_append;

        if constexpr (is_same_view_v<view::alias_t,m_operand_t>) {
            return fold_operand(state,m_operand.array);
        } else if constexpr (is_broadcast_view_v<m_operand_t>) {
            return fold_operand(state,at(get_operands(m_operand),ct_v<0>));
        } else if constexpr (is_view_v<m_operand_t>) {
            // view operand: fold its subtree
            auto sub             = fold(m_operand);
            auto sub_composition = at(sub,ct_v<0>);
            auto sub_leaves      = at(sub,ct_v<1>);

            // bury depth
            constexpr auto N_PARK = remove_cvref_t<decltype(at(state,ct_v<4>))>::value
                + len_v<decltype(at(state,ct_v<3>))>;

            auto new_state = nmtools_tuple{
                tuple_append(at(state,ct_v<0>),sub_composition),
                tuple_append(at(state,ct_v<1>),sub_leaves),
                tuple_append(at(state,ct_v<2>),ct_v<N_PARK>),
                at(state,ct_v<3>),
                ct_v<remove_cvref_t<decltype(at(state,ct_v<4>))>::value + len_v<decltype(sub_leaves)>>
            };

            return new_state;
        } else {
            auto new_state = nmtools_tuple{
                at(state,ct_v<0>),
                at(state,ct_v<1>),
                at(state,ct_v<2>),
                tuple_append(at(state,ct_v<3>),operand),
                at(state,ct_v<4>)
            };
            return new_state;
        }
    }

    template <typename view_t>
    constexpr auto fold(const view_t& view)
    {
        if constexpr (is_maybe_v<view_t>) {
            using view_type = get_maybe_type_t<view_t>;
            using result_t  = remove_cvref_t<decltype(fold(meta::declval<view_type>()))>;
            using return_t  = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (view
                ? return_t{fold(*view)}
                : return_t{Nothing}
            );
        } else if constexpr (is_either_v<view_t>) {
            using left_t    = get_either_left_t<view_t>;
            using right_t   = get_either_right_t<view_t>;
            using l_result_t = remove_cvref_t<decltype(fold(meta::declval<left_t>()))>;
            using r_result_t = remove_cvref_t<decltype(fold(meta::declval<right_t>()))>;
            using return_t = conditional_t<is_same_v<l_result_t,r_result_t>
                , l_result_t, nmtools_either<l_result_t,r_result_t>>;
            if (auto view_ptr = nmtools::get_if<left_t>(&view)) {
                return return_t{fold(*view_ptr)};
            } else /* if (auto view_ptr = nmtools::get_if<right_t>(&view)) */ {
                return return_t{fold(*nmtools::get_if<right_t>(&view))};
            }
        } else {
            static_assert( is_view_v<remove_cvref_t<view_t>>
                , "fold: expect a view expression" );
            
            auto operands = get_operands(view);

            static_assert( !is_fail_v<decltype(operands)>
                , "fold: unsupported operands for the given view");
            constexpr auto N = len_v<decltype(operands)>;

            auto init = nmtools_tuple{
                nmtools_tuple{}, nmtools_tuple{}, nmtools_tuple{}, nmtools_tuple{}
                , ct_v<0>
            };
            auto state = template_reduce<N>([&](auto init, auto index){
                const auto& operand = at(operands,index);
                return fold_operand(init,operand);
            }, init);

            auto compositions  = nmtools::get<0>(state);
            auto sub_leaves    = nmtools::get<1>(state);
            auto depths        = nmtools::get<2>(state);
            auto direct_leaves = nmtools::get<3>(state);

            auto f = get_function(view);
            constexpr auto K = len_v<decltype(compositions)>;
            auto composition = template_reduce<K>([&](auto init, auto index){
                using depth_t = remove_cvref_t<decltype(at(depths,index))>;
                constexpr auto D = depth_t::value;
                auto sub = at(compositions,index);
                if constexpr (D > 0) {
                    return init * combinator::bury_n<D> * sub;
                } else {
                    return init * sub;
                }
            }, f);

            // initial stack
            auto leaves = utility::tuple_cat(
                template_reduce<K>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    constexpr auto R = (K-1) - I;
                    return utility::tuple_cat(init, at(sub_leaves,ct_v<R>));
                }, nmtools_tuple{})
                , direct_leaves
            );

            return nmtools_tuple{composition,leaves};
        }
    } // fold
} // namespace nmtools::functional

#endif // NMTOOLS_CORE_FOLD_HPP
