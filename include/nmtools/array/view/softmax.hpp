#ifndef NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP
#define NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP

#include "nmtools/array/core/alias.hpp"
#include "nmtools/array/view/ufuncs/exp.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/maximum.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"

namespace nmtools::view
{
    /**
     * @brief Applies softmax function along specified axis
     * 
     * @tparam input_t 
     * @tparam axis_t 
     * @param input input array
     * @param axis  axis where softmax to be applied
     * @return constexpr auto 
     */
    template <typename input_t, typename axis_t>
    constexpr auto softmax(const input_t& input, axis_t axis)
    {
        auto a_input = view::aliased(input);
        // following pytorch, only allow index axis (index array axis not allowed)
        static_assert( meta::is_index_v<axis_t>
            , "unsupported softmax, expect axis to be index"
        );
        // NOTE: this follow https://cs231n.github.io/linear-classify/#softmax for numerical stability
        auto a = view::reduce_maximum(a_input,axis,/*dtype=*/None,/*initial=*/None,/*keepdims=*/True);
        auto b = view::subtract(a_input,a);
        auto c = view::exp(b);
        auto d = view::reduce_add(c,axis,/*dtype=*/None,/*initial=*/None,/*keepdims=*/True);
        return view::divide(c,d);
    } // softmax
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP