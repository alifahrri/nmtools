#ifndef NMTOOLS_ARRAY_ARRAY_COPY_HPP
#define NMTOOLS_ARRAY_ARRAY_COPY_HPP

#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto copy(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto ref_ = view::ref(array);
        return eval(ref_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // copy
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_COPY_HPP