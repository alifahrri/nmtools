#ifndef NMTOOLS_ARRAY_ARRAY_SLICE_HPP
#define NMTOOLS_ARRAY_ARRAY_SLICE_HPP

#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, template<typename...>typename tuple_t, typename...slices_t>
    constexpr auto apply_slice(const array_t& array, const tuple_t<slices_t...>& slices,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::apply_slice(array,slices);
        // NOTE: providing context and output variable makes
        // the compiler confused, for now pass context and output
        // as type only
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    }

    template <typename array_t, typename...slices_t>
    constexpr auto slice(const array_t& array, slices_t...slices)
    {
        #if 0
        auto a = view::slice(array,slices...);
        // NOTE: providing context and output variable makes
        // the compiler confused, for now pass context and output
        // as type only
        using output_t   = none_t;
        using context_t  = none_t;
        using resolver_t = eval_result_t<>;
        return eval(a,context_t{},output_t{},meta::as_value_v<resolver_t>);
        #else
        auto slices_pack = nmtools_tuple{slices...};
        return apply_slice(array,slices_pack);
        #endif
    }
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SLICE_HPP