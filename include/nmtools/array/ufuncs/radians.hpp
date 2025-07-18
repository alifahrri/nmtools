#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_RADIANS_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_RADIANS_HPP

#include "nmtools/constants.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"

namespace nmtools::view
{
    template <typename array_t>
    constexpr auto radians(const array_t& a)
    {
        using element_t = meta::get_element_type_t<array_t>;
        constexpr auto b = pi_v<element_t> / 180;
        return view::multiply(a,b);
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_RADIANS_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_UFUNCS_RADIANS_HPP
#define NMTOOLS_ARRAY_ARRAY_UFUNCS_RADIANS_HPP

#include "nmtools/array/ufuncs/radians.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t>
    constexpr auto radians(const array_t& array
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::radians(array);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_UFUNCS_RADIANS_HPP