#ifndef NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP
#define NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP

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
     * @tparam dim_t 
     * @param input input array
     * @param dim   axis where softmax to be applied
     * @return constexpr auto 
     */
    template <typename input_t, typename dim_t>
    constexpr auto softmax(const input_t& input, dim_t dim)
    {
        // following pytorch, only allow index dim (index array dim not allowed)
        static_assert( meta::is_index_v<dim_t>
            , "unsupported softmax, expect dim to be index"
        );
        // NOTE: this follow https://cs231n.github.io/linear-classify/#softmax for numerical stability
        auto input_    = view::subtract(input,view::reduce_maximum(input,/*axis=*/dim,/*dtype=*/None,/*initial=*/None,/*keepdims=*/True));
        auto input_exp = view::exp(input_);
        auto reduced   = view::reduce_add(input_exp,/*axis=*/dim,/*dtype=*/None,/*initial=*/None,/*keepdims=*/True);
        return view::divide(input_exp,reduced);
    } // softmax
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP