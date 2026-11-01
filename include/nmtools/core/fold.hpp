#ifndef NMTOOLS_CORE_FOLD_HPP
#define NMTOOLS_CORE_FOLD_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/apply.hpp"
#include "nmtools/core/combinator.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::functional
{
    /**
     * @brief Fold a (lazily composed) view expression into a point-free function
     * composition paired with its operands.
     *
     * The returned tuple `{function, operands}` is the typed execution capture:
     * - `function`  : `functor_t`/`functor_composition_t`, the whole expression as a
     *   single point-free program (same shape of product as
     *   `get_function(linearize(get_compute_graph(view)))`, without building a graph);
     * - `operands`  : tuple of leaf operands, arrays by-ref (or by-pointer when they
     *   come wrapped, e.g. aliased) and numbers by-value.
     *
     * `functional::apply(function, operands)` rebuilds the original lazy view
     * expression, and device contexts can `map_to_device(function)` then
     * `run(function, output, operands)` directly.
     *
     * The fold walks the expression post-order:
     * - leaf operands (arrays/numbers) are collected as-is;
     * - transparent decorators (`view::alias_t`, broadcast views) are peeled, ufunc
     *   fmaps handle aliasing/broadcasting internally;
     * - each view operand contributes its own sub-composition;
     * - the parent functor is composed with the sub-compositions such that they apply
     *   in reverse operand order, interleaved with `combinator::bury` so that each
     *   sub-result is parked exactly at its operand position when the parent applies.
     *
     * Note that shared subexpressions are *not* deduplicated: each syntactic
     * occurrence contributes its own leaves. Deduplication (CSE) is the job of the
     * tree/graph passes; the fold is behavior-preserving regardless.
     *
     * @note Apply the returned function with *all* operands at once (e.g. via
     * `functional::apply`, as the device kernels do). The composition is a stack
     * machine whose intermediate states hold maybe-wrapped views (view constructors
     * return maybes); partially applying it operand-by-operand surfaces those
     * intermediate states as maybe-wrapped curried compositions, which cannot be
     * called further.
     */
    namespace detail
    {
        // forward declaration: fold_operand and fold_view are mutually recursive
        template <typename view_t>
        constexpr auto fold_view(const view_t& view);

        /**
         * @brief Process one operand of a view during the fold, updating the fold state.
         *
         * The operand may be pointer-wrapped and may be wrapped by transparent
         * decorators (`view::alias_t`, broadcast views), which are peeled recursively.
         *
         * State slots (a flat tuple):
         * 0. compositions  : tuple of sub-compositions, one per view operand (operand order)
         * 1. sub_leaves    : tuple of leaf tuples, one per view operand (operand order)
         * 2. depths        : tuple of `ct<D>`, the bury depth per view operand
         * 3. direct_leaves : tuple of direct leaf operands (operand order)
         * 4. n_leaves      : `ct<N>`, total number of leaves collected so far
         */
        template <typename state_t, typename operand_t>
        constexpr auto fold_operand(state_t state, const operand_t& operand)
        {
            // normalize pointer-wrapped operands to the pointee for type inspection
            const auto& entity = [&]() -> decltype(auto) {
                using operand_raw_t = remove_cvref_t<operand_t>;
                if constexpr (is_pointer_v<operand_raw_t>) {
                    return (*operand);
                } else {
                    return (operand);
                }
            }();
            using entity_t = remove_cvref_t<decltype(entity)>;

            if constexpr (is_same_view_v<view::alias_t,entity_t>) {
                // alias is transparent, continue with the aliased operand
                // (arrays stay wrapped as pointer, matching the device operand contract)
                return fold_operand(state, entity.array);
            } else if constexpr (is_broadcast_view_v<entity_t>) {
                // broadcast wrapper is transparent, ufunc fmaps broadcast internally
                return fold_operand(state, nmtools::at(get_operands(entity),ct_v<0>));
            } else if constexpr (is_view_v<entity_t>) {
                // view operand: fold its subtree
                auto sub              = fold_view(entity);
                auto sub_composition  = nmtools::at(sub,ct_v<0>);
                auto sub_leaves       = nmtools::at(sub,ct_v<1>);

                // bury depth: park this sub-result below the leaves of the subtrees
                // that apply after it (reverse order), plus the direct leaves that
                // sit before this operand.
                constexpr auto N_PARK = remove_cvref_t<decltype(nmtools::get<4>(state))>::value
                    + len_v<decltype(nmtools::get<3>(state))>;
                auto new_state = nmtools_tuple{
                    utility::tuple_append(nmtools::get<0>(state),sub_composition),
                    utility::tuple_append(nmtools::get<1>(state),sub_leaves),
                    utility::tuple_append(nmtools::get<2>(state),ct_v<N_PARK>),
                    nmtools::get<3>(state),
                    ct_v<remove_cvref_t<decltype(nmtools::get<4>(state))>::value
                        + len_v<decltype(sub_leaves)>>
                };
                return new_state;
            } else {
                // direct leaf: array (by-ref or by-pointer) or number, kept as-is
                auto new_state = nmtools_tuple{
                    nmtools::get<0>(state),
                    nmtools::get<1>(state),
                    nmtools::get<2>(state),
                    utility::tuple_append(nmtools::get<3>(state),operand),
                    nmtools::get<4>(state)
                };
                return new_state;
            }
        } // fold_operand

        /**
         * @brief Fold a view (already unwrapped from maybe/either) into
         * `{function_composition, operands_tuple}`.
         */
        template <typename view_t>
        constexpr auto fold_view(const view_t& view)
        {
            using view_type [[maybe_unused]] = remove_cvref_t<view_t>;
            auto operands = get_operands(view);
            static_assert( !is_fail_v<decltype(operands)>
                , "fold: unsupported operands for the given view" );
            constexpr auto N = len_v<decltype(operands)>;

            // forward pass over operands
            auto state = template_reduce<N>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                const auto& operand = nmtools::at(operands,ct_v<I>);
                return fold_operand(init,operand);
            }, nmtools_tuple{
                nmtools_tuple{}, nmtools_tuple{}, nmtools_tuple{}, nmtools_tuple{}
                , ct_v<0>
            });

            auto compositions  = nmtools::get<0>(state);
            auto sub_leaves    = nmtools::get<1>(state);
            auto depths        = nmtools::get<2>(state);
            auto direct_leaves = nmtools::get<3>(state);

            // compose the point-free program. The composition applies right-to-left;
            // appending `[bury<d_i>, P_i]` in operand order makes each subtree program
            // apply in reverse operand order with its bury right after it:
            //   applied: P_k, bury<d_k>, ..., P_1, bury<d_1>, parent
            auto parent = get_function(view);
            constexpr auto K = len_v<decltype(compositions)>;
            auto composition = template_reduce<K>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                using depth_t = remove_cvref_t<decltype(nmtools::get<I>(depths))>;
                constexpr auto D = depth_t::value;
                auto sub = nmtools::get<I>(compositions);
                if constexpr (D > 0) {
                    return init * combinator::bury_n<D> * sub;
                } else {
                    return init * sub;
                }
            }, parent);

            // initial stack: subtree leaves in reverse operand order, direct leaves last
            auto leaves = utility::tuple_cat(template_reduce<K>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                constexpr auto R = (K-1) - I;
                return utility::tuple_cat(init, nmtools::get<R>(sub_leaves));
            }, nmtools_tuple{}),direct_leaves);

            return nmtools_tuple{composition,leaves};
        } // fold_view
    } // namespace detail

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
            return detail::fold_view(view);
        }
    } // fold
} // namespace nmtools::functional

#endif // NMTOOLS_CORE_FOLD_HPP
