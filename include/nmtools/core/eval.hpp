#ifndef NMTOOLS_ARRAY_EVAL_HPP
#define NMTOOLS_ARRAY_EVAL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/utility/get.hpp"

#include "nmtools/utility/isequal.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/apply_resize.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/tuple_cat.hpp"

#include "nmtools/index/compute_offset.hpp"

#include "nmtools/core/context.hpp"

namespace nmtools
{
    // TODO: move
    enum LayoutKind : int
    {
        UNKNOWN_LAYOUT=-999,
        RowMajor=-1,
        ColumnMajor=0,
    };
}

namespace nmtools
{
    // TODO: remove, should use get_operands
    template <typename array_t>
    decltype(auto) get_array(const array_t& array);

    // TODO: remove, should use get_operands
    template <typename array_t>
    struct get_array_t
    {
        constexpr inline auto operator()(const array_t& array) const
        {
            if constexpr (meta::is_view_v<array_t>) {
                return get_array(array.array);
            } else if constexpr (meta::is_tuple_v<array_t>) {
                constexpr auto N = meta::len_v<array_t>;
                if constexpr (N == 1) {
                    return get_array(nmtools::get<0>(array));
                } else {
                    return meta::template_reduce<N>([&](auto init, auto index){
                        constexpr auto I = decltype(index)::value;
                        return utility::tuple_append(init,get_array(nmtools::get<I>(array)));
                    }, nmtools_tuple{});
                }
            } else if constexpr (meta::is_pointer_v<array_t>) {
                return array;
            } else if constexpr (meta::is_ndarray_v<array_t>) {
                return &array;
            } else if constexpr (meta::is_num_v<array_t>) {
                // return copy
                return array;
            } else {
                static_assert(
                    meta::is_view_v<array_t>
                    || meta::is_pointer_v<array_t>
                    || meta::is_ndarray_v<array_t>
                    || meta::is_tuple_v<array_t>
                    || meta::is_num_v<array_t>
                    , "unsupported array type"
                );
            }
        }
    }; // get_array_t

    // TODO: remove, should use get_operands
    template <typename array_t>
    decltype(auto) get_array(const array_t& array)
    {
        constexpr auto f_obj = get_array_t<array_t>{};
        // should return pointer or tuple of pointer
        return f_obj(array);
    }

    /**
     * @brief Evaluate a view, given context and optional output.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam view_t 
     * @param view 
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t, typename view_t>
    constexpr auto eval(const view_t& view, context_t&& context, output_t&& output=output_t{})
    {
        // put context first so it can decide how to handle either, maybe etc.
        // e.g. object context may want to unwrap after eval
        if constexpr (is_context_v<context_t>) {
            return context.eval(output,view);
        } else if constexpr (is_context_ptr_v<context_t>) {
            return context->eval(output,view);
        } else {
            // TODO: error
        }
    }

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
        template <typename output_t, typename context_t, typename views_t, template<auto...>typename index_sequence, auto...Is>
        constexpr auto apply_eval(const views_t& views, context_t&& context, output_t&& output, index_sequence<Is...>)
        {
            return nmtools_tuple{nmtools::eval(nmtools::get<Is>(views)
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output))
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
    template <typename output_t=none_t
        , typename context_t
        , typename views_t>
    constexpr auto apply_eval(const views_t& views
        , context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        if constexpr (meta::is_maybe_v<views_t>) {
            using views_type  = meta::get_maybe_type_t<views_t>;
            using result_type = decltype(apply_eval(
                  meta::declval<views_type>()
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
            ));
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>,result_type,nmtools_maybe<result_type>>;
            if (static_cast<bool>(views)) {
                return return_type{apply_eval(*views
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                )};
            } else {
                return return_type{meta::Nothing};
            }
        } else if constexpr (meta::is_list_v<views_t>) {
            using eval_t = decltype(eval(at(views,0)
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
            ));
            using result_t = meta::replace_value_type_t<views_t,eval_t>;
            auto res = result_t {};
            auto n = len(views);
            for (size_t i=0; i<n; i++) {
                auto view_i = at(views,i);
                res.push_back(eval(view_i
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                ));
            }
            return res;
        } else {
            constexpr auto N = meta::len_v<views_t>;
            return detail::apply_eval(views
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , meta::make_index_sequence_v<N>
            );
        }
    } // apply_eval

} // namespace nmtools

// TODO: remove these includes
#include "nmtools/ndarray/base_ndarray.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/ndarray.hpp"

#endif // NMTOOLS_ARRAY_EVAL_HPP