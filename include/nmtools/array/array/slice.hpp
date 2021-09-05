#ifndef NMTOOLS_ARRAY_ARRAY_SLICE_HPP
#define NMTOOLS_ARRAY_ARRAY_SLICE_HPP

#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename...slices_t>
    constexpr auto slice(const array_t& array, slices_t...slices)
    {
        auto a = view::slice(array,slices...);
        // NOTE: providing context and output variable makes
        // the compiler confused, for now pass context and output
        // as type only
        return eval(a,context_t{},output_t{});
    }
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SLICE_HPP