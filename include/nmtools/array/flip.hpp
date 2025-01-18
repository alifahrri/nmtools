#ifndef NMTOOLS_ARRAY_VIEW_FLIP_HPP
#define NMTOOLS_ARRAY_VIEW_FLIP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/index/flip.hpp"
#include "nmtools/array/slice.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::view
{
    /**
     * @brief Reverse the order of elements of given array according to specified axis.
     *
     * Axis can be None, a single integer, or index_array.
     * For None axis, reverse all original axis.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array array in which its elements are to be reversed
     * @param axis axis to operate
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t>
    constexpr inline auto flip(const array_t& array, const axis_t& axis)
    {
        auto a_dim  = dim<true>(array);
        auto slices = index::flip_slices(a_dim,axis);
        return apply_slice(array,slices);
    } // flip

    template <typename array_t>
    constexpr inline auto flipud(const array_t& array)
    {
        return view::flip(array,meta::ct_v<0>);
    } // flipud

    template <typename array_t>
    constexpr inline auto fliplr(const array_t& array)
    {
        return view::flip(array,meta::ct_v<1>);
    } // fliplr
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_FLIP_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/flip.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct flip_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::flip(args...);
            }
        };

        struct fliplr_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::fliplr(args...);
            }
        };

        struct flipud_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::flipud(args...);
            }
        };
    }

    constexpr inline auto flip   = functor_t{unary_fmap_t<fun::flip_t>{}};
    constexpr inline auto fliplr = functor_t{unary_fmap_t<fun::fliplr_t>{}};
    constexpr inline auto flipud = functor_t{unary_fmap_t<fun::flipud_t>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_FLIP_HPP
#define NMTOOLS_ARRAY_ARRAY_FLIP_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/flip.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate flip
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array array to be flipped
     * @param axis axis to operate on
     * @param context exectution context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t>
    constexpr auto flip(const array_t& array, const axis_t& axis,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto flipped = view::flip(array,axis);
        return eval(flipped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // flip

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto fliplr(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto flipped = view::fliplr(array);
        return eval(flipped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // fliplr

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto flipud(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto flipped = view::flipud(array);
        return eval(flipped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // flipud
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FLIP_HPP