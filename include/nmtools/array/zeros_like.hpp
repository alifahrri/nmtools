#ifndef NMTOOLS_ARRAY_VIEW_ZEROS_LIKE_HPP
#define NMTOOLS_ARRAY_VIEW_ZEROS_LIKE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/full.hpp"

namespace nmtools::view
{
    template <typename array_t, typename dtype_t=none_t>
    constexpr auto zeros_like(const array_t& array, dtype_t=dtype_t{})
    {
        auto element_vtype = [](){
            if constexpr (is_none_v<dtype_t>) {
                using element_t = meta::get_element_type_t<array_t>;
                return meta::as_value_v<element_t>;
            } else {
                using element_t = get_dtype_t<dtype_t>;
                return meta::as_value_v<element_t>;
            }
        }();
        using element_t = meta::type_t<decltype(element_vtype)>;
        auto src_shape  = shape<true>(array);
        return full(src_shape,static_cast<element_t>(0));
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ZEROS_LIKE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ZEROS_LIKE_HPP
#define NMTOOLS_ARRAY_ARRAY_ZEROS_LIKE_HPP

#include "nmtools/array/zeros_like.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename dtype_t=none_t>
    constexpr auto zeros_like(const array_t& array, dtype_t dtype=dtype_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::zeros_like(array,dtype);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // zeros_like
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ZEROS_LIKE_HPP