#ifndef NMTOOLS_ARRAY_ARRAY_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_ARRAY_BROADCAST_TO_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename shape_t>
    constexpr auto broadcast_to(const array_t& array, shape_t& shape,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto broadcasted = view::broadcast_to(array,shape);
        return eval(broadcasted,context,output);
    } // broadcast_to
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_BROADCAST_TO_HPP