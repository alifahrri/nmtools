#ifndef NMTOOLS_ARRAY_ARRAY_SPLIT_HPP
#define NMTOOLS_ARRAY_ARRAY_SPLIT_HPP

#include "nmtools/array/view/split.hpp"
#include "nmtools/array/eval.hpp"

#include "nmtools/utility/forward.hpp"

namespace nmtools::array
{
    namespace detail
    {
        /**
         * @brief Helper function apply eval on tuple of views
         * 
         * @tparam output_t 
         * @tparam context_t 
         * @tparam views_t 
         * @tparam index_sequence 
         * @tparam Is 
         * @param views     tuple of view
         * @param context   eval context
         * @param output 
         * @return constexpr auto 
         */
        template <typename output_t, typename context_t, typename resolver_t, typename views_t, template<auto...>typename index_sequence, auto...Is>
        constexpr auto apply_eval(const views_t& views, context_t&& context, output_t&& output, resolver_t resolver, index_sequence<Is...>)
        {
            return nmtools_tuple{array::eval(nmtools::get<Is>(views)
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver)
                ...
            };
        } // apply_eval
    } // namespace detail

    /**
     * @brief Helper function to apply eval for each tuple on tuple of views
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam views_t 
     * @param views     tuple of view
     * @param context   eval context
     * @param output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t
        , typename views_t>
    constexpr auto apply_eval(const views_t& views
        , context_t&& context=context_t{}, output_t&& output=output_t{}
        , meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        if constexpr (meta::is_list_v<views_t>) {
            using eval_t = decltype(eval(at(views,0)
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver
            ));
            using result_t = meta::replace_value_type_t<views_t,eval_t>;
            auto res = result_t {};
            auto n = len(views);
            for (size_t i=0; i<n; i++) {
                auto view_i = at(views,i);
                res.push_back(eval(view_i
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                ));
            }
            return res;
        } else {
            constexpr auto N = meta::len_v<views_t>;
            return detail::apply_eval(views
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver
                , meta::make_index_sequence_v<N>
            );
        }
    } // apply_eval

    /**
     * @brief Eagerly split an array
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam index_t 
     * @tparam axis_t 
     * @param array 
     * @param indices_or_sections 
     * @param axis 
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t
        , typename array_t, typename index_t, typename axis_t>
    constexpr auto split(const array_t& array, const index_t& indices_or_sections, axis_t axis
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto split_ = view::split(array,indices_or_sections,axis);
        return apply_eval(split_
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SPLIT_HPP